/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thibnguy <thibnguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 20:01:34 by thibnguy          #+#    #+#             */
/*   Updated: 2023/09/07 15:08:44 by thibnguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_cmd	*ft_parser(t_data *data)
{
	t_data	*head_data;
	t_data	*head_pipe;
	t_data	*after_pipe;
	t_cmd	*head_cmd;
	t_cmd	*cmd;
	char	**split;
	int		i;
	int		j;
	int		test;

	test = 0;
	cmd = NULL;
	head_data = data;
	printf("HEAD DATA : ");
	ft_print_data(head_data);
	head_pipe = head_data;
	head_cmd = cmd;
	while (1)
	{
		addlast_cmd(&head_cmd, ft_new_cmd());
		if (cmd == NULL)
			cmd = head_cmd;
		else
			cmd = (cmd)->next;
		// While not pipe and didn't come back to the beggggginnnning de la liste chainee
		while (data->token != 0)
		{
			// If redirection
			if (data->token != 5)
			{
				if ((data->next)->exit_code == 3)
				{
					printf("Error\n");
					ft_free_stack(data);
					exit(EXIT_FAILURE);
				}
				// Store redirection and data->next dans redirection list
				// ET Supprimer de data la redirection et son argument
				addlast_node(&(cmd->redirections), ft_data_copy(data));
				data = data->prev;
				data->next = data->next->next;
				(data->next)->prev = data;
				data = data->next;
				split = ft_split(data->content, " ");
				addlast_node(&(cmd->redirections), ft_new_stack(ft_strdup(split[0]), NULL));
				/*	Si y a rien appart le file on supprime de data
					Sinon on remplace data->content avec ce qu'il y a apres le file
				*/
				j = ft_count_words(data->content, " ");
				if (j == 1)
				{
					if (data == data->next)
					{
						test = 1;
						ft_free_stack(data);
					}
					else
					{
						data = data->prev;
						data->next = data->next->next;
						(data->next)->prev = data;
					}
				}
				else
					data->content = ft_strjoin(data->content, ft_substr(data->content, ft_strlen(split[0]) + 1, ft_strlen(data->content) - ft_strlen(split[0]) + 1));
				i = 0;
				while (i < j)
					free(split[i++]);
				free(split);
			}
			if (test)
			{
				printf("JE SUIS LA\n");
				break ;
			}
			data = data->next;
			printf("DATA : ");
			ft_print_data(data);
			if (data == head_data || data->next == data)
				break ;
		}
		if (test)
		{
			cmd->command = NULL;
			break ;
		}
		if (data == head_data)
			after_pipe = data;
		else
			after_pipe = data->next;
		data = head_pipe;
		i = ft_count_words(data->content, " ");
		cmd->command = malloc(sizeof(char *) * (i + 1));
		if (!cmd->command)
			return (NULL);
		split = ft_split(data->content, " ");
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
		data = after_pipe;
		head_pipe = data;
		if (data == head_data)
			break;
	}
	data = head_data;
	cmd = head_cmd;
	return (cmd);
}