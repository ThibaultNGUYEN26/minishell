/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchbouki <rchbouki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 20:01:34 by thibnguy          #+#    #+#             */
/*   Updated: 2023/09/08 18:01:04 by rchbouki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_cmd	*ft_parser(t_data **data)
{
	t_data	*head_data;
	t_data	*head_pipe;
	t_data	*after_pipe;
	t_cmd	*head_cmd;
	t_cmd	*cmd;
	char	**split;
	int		i;
	int		j;
	
	cmd = NULL;
	head_data = *data;
	head_pipe = head_data;
	head_cmd = cmd;
	while (1)
	{
		/* Ajouter une commande qui va prendre tout ce qu'il y avait avant le pipe, si c'est le premier element on le mets à head_cmd sinon on passe au suivant après avoir ajouté une nouvelle commande dans la liste */
		addlast_cmd(&head_cmd, ft_new_cmd());
		if (cmd == NULL)
			cmd = head_cmd;
		else
			cmd = (cmd)->next;
		// While not pipe and didn't come back to the beggggginnnning de la liste chainee
		while ((*data)->token != 0)
		{
			// If redirection
			if ((*data)->token != 5)
			{
				// si file invalid ou pas de file, on free et on arrete tout (faut pas exit normalement)
				if (((*data)->next)->exit_code == 3)
				{
					printf("minishell: syntax error near unexpected token\n");
					(*data) = (*data)->next;
					break ;
				}
				if (((*data)->next)->exit_code == 2)
				{
					printf("minishell: unexpected EOF while looking for matching quote\nminishell: syntax error: unexpected end of file\n");
					(*data) = (*data)->next;
					break ;
				}
				// Store redirection dans cmd->redirection ET Supprimer de data la redirection
				addlast_node(&(cmd->redirections), ft_data_copy((*data)));
				(*data) = (*data)->prev;
				(*data)->next = (*data)->next->next;
				((*data)->next)->prev = (*data);
				// Store file of redirection dans cmd->redirection et split le mot in case other words that are NOT the file were AFTER the file
				(*data) = (*data)->next;
				split = ft_split((*data)->content, "\f\t\n\r\v ");
				addlast_node(&(cmd->redirections), ft_new_stack(ft_strdup(split[0]), NULL));
				/*	Si il n'y a rien appart le file on supprime de data
					Sinon on remplace data->content avec ce qu'il y a apres le file */
				j = ft_count_words((*data)->content, "\f\t\n\r\v ");
				/* Si il n'y avait que un seul mot dans QUE le file, on peut le supprimer de data
				   Sinon on remplace data avec ce qu'il y avait après */
				if (j == 1)
				{
					// Si il ne reste plus que le file, on doit free data et la mettre à NULL, sinon on supprime avec next et prev
					if ((*data) == (*data)->next)
					{
						//test = 1;
						ft_free_stack((*data));
						(*data) =  NULL;
					}
					else
					{
						free((*data)->content);
						(*data) = (*data)->prev;
						(*data)->next = (*data)->next->next;
						((*data)->next)->prev = (*data);
					}
				}
				else
					(*data)->content = ft_strjoin((*data)->content, ft_substr((*data)->content, ft_strlen(split[0]) + 1, ft_strlen((*data)->content) - ft_strlen(split[0]) + 1));
				i = 0;
				while (i < j)
					free(split[i++]);
				free(split);
			}
			// Si data est NULL it means everything was deleted from it, end of loop
			if ((*data) == NULL)
				break ;
			(*data) = (*data)->next;
			if ((*data) == head_data || (*data)->next == (*data))
				break ;
		}
		// Si data est NULL it means everything was deleted from it, end of loop et on doit mettre cmd->command = NULL sinon on segfault dans ft_parser_print
		if ((*data) == NULL || (*data)->exit_code == 3 || (*data)->exit_code == 2)
		{
			cmd->command = NULL;
			break ;
		}
		// On remplit la cmd->command avec la commande aka ce qui reste dans la structure du lexer
		if ((*data) == head_data)
			after_pipe = (*data);
		else
			after_pipe = (*data)->next;
		(*data) = head_pipe;
		i = ft_count_words((*data)->content, "\f\t\n\r\v ");
		cmd->command = malloc(sizeof(char *) * (i + 1));
		if (!cmd->command)
			return (NULL);
		split = ft_split((*data)->content, "\f\t\n\r\v ");
		j = 0;
		while (j < i)
		{
			cmd->command[j] = ft_strdup(split[j]);
			j++;
		}
		cmd->command[j] = NULL;
		i = 0;
		while (i < j)
			free(split[i++]);
		free(split);
		(*data) = after_pipe;
		head_pipe = (*data);
		if ((*data) == head_data)
			break;
	}
	// Si data n'existe plus, no need to put it back where it once was
	if ((*data) != NULL && (*data)->exit_code != 3 && (*data)->exit_code != 2)
		(*data) = head_data;
	cmd = head_cmd;
	return (cmd);
}
