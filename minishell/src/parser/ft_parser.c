/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchbouki <rchbouki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 20:01:34 by thibnguy          #+#    #+#             */
/*   Updated: 2023/10/08 20:56:05 by rchbouki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/* Si file invalid ou pas de file
	==> on free, on arrete tout et on repart à la minishell loop */
static int	ft_invalid_redirec(t_data **data, t_data *head_data)
{
	if (((*data)->next)->exit_code == 1)
	{
		printf("minishell: syntax error near unexpected token `newline'\n");
		(*data) = head_data;
		(*data)->exit_code = 2;
		exit_code = 2;
		return (1);
	}
	if ((*data)->next == head_data)
	{
		printf("minishell: syntax error near unexpected token `newline'\n");
		(*data) = head_data;
		(*data)->exit_code = 2;
		exit_code = 2;
		return (1);
	}
	return (0);
}

static int	ft_redirection_parser(t_data **head_data, t_data **data, t_cmd *cmd, t_data **head_pipe)
{
	char	**split;
	char	*temp;
	int		i;
	int		j;
	
	// If redirection
	if ((*data)->token != 5)
	{
		if (ft_invalid_redirec(data, *head_data))
			return (0);
		// Store redirection dans cmd->redirection ET Supprimer de data la redirection (+ Update head_data)
		addlast_node(&(cmd->redirections), ft_data_copy((*data)));
		if ((*data) == *head_data)
			*head_data = (*data)->next;
		if (*head_pipe == *data)
			*head_pipe = (*data)->next;
		ft_delete_element(data);
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
			if ((*data) == *head_data)
				*head_data = (*data)->next;
			if (*head_pipe == *data)
				*head_pipe = (*data)->next;
			ft_delete_element(data);
		}
		else
		{
			temp = ft_substr((*data)->content, ft_strlen(split[0]) + 1, ft_strlen((*data)->content) - ft_strlen(split[0]) + 1);
			free((*data)->content);
			(*data)->content = ft_strdup(temp);
			free(temp);
		}
		i = 0;
		while (i < j)
			free(split[i++]);
		free(split);
	}
	return (1);
}

static int	ft_echo_errors(t_data **data, t_cmd *cmd, int i, char **split)
{
	int	k;
	int	j;
	int	ancien;
	int	test;
	
	k = 0;
	j = 0;
	test = 0;
	cmd->command[j++] = ft_strdup(split[k++]);
	while (ft_strncmp((*data)->content + i, "echo", 3) != 0)
		i++;
	i += 4;
	while (1)
	{
		while (((*data)->content)[i] != '-' && (((*data)->content)[i] == '\f' || ((*data)->content)[i] == '\t' || ((*data)->content)[i] == '\n' || ((*data)->content)[i] == '\r' || ((*data)->content)[i] == '\v' || ((*data)->content)[i] == ' '))
			i++;
		if (((*data)->content)[i] == '-')
		{
			ancien = i;
			i++;
			if (((*data)->content)[i] != 'n')
			{
				cmd->command[j++] = ft_substr((*data)->content, ancien, ft_strlen((*data)->content) - ancien);
				test = 1;
				break ;
			}
			while (((*data)->content)[i] == 'n')
				i++;
			// if there is nothing apres le n it means c'est bien un -n sans rien d'ajouté donc c'est une OPTION de echo et pas genre -nnnnnriri
			if (((*data)->content)[i] == '\f' || ((*data)->content)[i] == '\t' || ((*data)->content)[i] == '\n' || ((*data)->content)[i] == '\r' || ((*data)->content)[i] == '\v' || ((*data)->content)[i] == ' ')
				cmd->command[j++] = ft_strdup(split[k++]);
			else
			{
				cmd->command[j++] = ft_substr((*data)->content, ancien, ft_strlen((*data)->content) - ancien);
				test = 1;
				break ;
			}
		}
		else
			break ;
	}
	if (test == 1)
		return (j);
	// if there echo is not just before, it means we have -n donc il faut skip les espaces
	while (((*data)->content)[i] == '\f' || ((*data)->content)[i] == '\t' || ((*data)->content)[i] == '\n' || ((*data)->content)[i] == '\r' || ((*data)->content)[i] == '\v' || ((*data)->content)[i] == ' ')
		i++;
	cmd->command[j++] = ft_substr((*data)->content, i, ft_strlen((*data)->content) - i);
	return (j);
}

static void	ft_command_parser(t_cmd *cmd, t_data **data, t_data *after_pipe)
{
	char	**split;
	t_data	*head;
	int		i;
	int		j;
	
	i = 0;
	j = 0;
	head = *data;
	// count the words from ALL contents left from data before pipe
	while (1)
	{
		i += ft_count_words((*data)->content, "\f\t\n\r\v ");
		*data = (*data)->next;
		if ((*data) == after_pipe)
			break;
	}
	cmd->command = malloc(sizeof(char *) * (i + 2));
	if (!cmd->command)
		return ;
	(*data) = head;
	// Fill the command with what's left
	while (1)
	{
		i = 0;
		split = ft_split((*data)->content, "\f\t\n\r\v ");
		printf("data : %s\n", (*data)->content);
		if (ft_strcmp(split[0], "echo") == 0)
			j = ft_echo_errors(data, cmd, i, split);
		else
			while (split[i])
				cmd->command[j++] = ft_strdup(split[i++]);
		i = 0;
		while (split[i])
			free(split[i++]);
		free(split);
		*data = (*data)->next;
		if ((*data) == after_pipe)
			break;
	}
	cmd->command[j] = NULL;
}

t_cmd	*ft_parser(t_data **data)
{
	t_data	*head_data;
	t_data	*head_pipe;
	t_data	*after_pipe;
	t_cmd	*head_cmd;
	t_cmd	*cmd;
	
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
			if (!ft_redirection_parser(&head_data, data, cmd, &head_pipe))
			{
				cmd->error = 1;
				return (cmd);
			}
			// Si data est NULL it means everything was deleted from it, end of loop
			if ((*data) == NULL)
				break ;
			(*data) = (*data)->next;
			if ((*data) == head_data || (*data)->next == (*data))
				break ;
		}
		// Si data est NULL it means everything was deleted from it, end of loop et on doit mettre cmd->command = NULL sinon on segfault dans ft_parser_print
		if ((*data) == NULL || (*data)->exit_code == 1 || (*data)->exit_code == 2)
		{
			cmd->command = NULL;
			break ;
		}
		// On remplit la cmd->command avec la commande aka ce qui reste dans la structure du lexer
		after_pipe = (*data);
		(*data) = head_pipe;
		ft_command_parser(cmd, data, after_pipe);
		if (after_pipe == head_data)
			(*data) = after_pipe;
		else
			(*data) = (after_pipe)->next;
		head_pipe = (*data);
		if ((*data) == head_data)
			break;
	}
	// Si data n'existe plus, no need to put it back where it once was
	if ((*data) != NULL && (*data)->exit_code != 1 && (*data)->exit_code != 2)
		(*data) = head_data;
	cmd = head_cmd;
	return (cmd);
}
