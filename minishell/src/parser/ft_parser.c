/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thibnguy <thibnguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 20:01:34 by thibnguy          #+#    #+#             */
/*   Updated: 2023/09/05 22:48:11 by thibnguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_parser(t_data *data)
{
	t_data	*head;
	t_data	*head_cmd;
	t_cmd	*cmd;
	char	**split;
	int		i;

	cmd = malloc(sizeof(t_cmd) * 1);
	if (!cmd)
		return ;
	head = data;
	head_cmd = head;
	while (1)
	{
		addlast_cmd(cmd, ft_new_cmd());
		// While not pipe and didn't come back to the beggggginnnning de la liste chainee
		while (data->token != 0 && data->next != head)
		{
			// If redirection
			if (data->token != 5)
			{
				// Store redirection and data->next dans redirection list
				// ET Supprimer de data la redirection et son argument
				add_last_node(cmd->redirections, data);
				data = data->prev;
				data->next = data->next->next;
				(data->next)->prev = data;
				data = data->next;
				split = ft_split(data->content, " ");
				add_last_node(cmd->redirections, ft_new_stack(split[0], NULL));
				/*	Si y a rien appart le file on supprime de data
					Sinon on remplace data->content avec ce qu'il y a apres le file
				*/
				if (ft_count_words(data->content, " ") == 1)
				{
					data = data->prev;
					data->next = data->next->next;
					(data->next)->prev = data;
				}
				else
					data->content = ft_strjoin(data->content, ft_substr(data->content, ft_strlen(split[0]) + 1, ft_strlen(data->content) - ft_strlen(split[0]) + 1));
			}
			data = data->next;
		}
		data = head_cmd;
		i = 0;
		while (data->token != 0 && data->next != head)
		{
			data = data->next;
			i++;
		}
		data = head_cmd;
		cmd->command = malloc(sizeof(char *) * i);
		if (!cmd->command)
			return ;
		i = 0;
		while (data->token != 0 && data->next != head)
		{
			cmd->command[i] = data->content;
			i++;
			data = data->next;
		}
		data = data->next;
		head_cmd = data;
		if (data->next == head)
			break;
		data = data->next;
	}
	data = head;
}