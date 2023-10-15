/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser_redirec.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thibnguy <thibnguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/15 11:34:44 by thibnguy          #+#    #+#             */
/*   Updated: 2023/10/15 14:29:27 by thibnguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/**
	* Checks if file is invalid or no file, free and mainloop again
	* @param t_data.**data
	* @param t_data.*head_data
	* @returns int
	*/
int	ft_invalid_redirec(t_data **data, t_data *head_data)
{
	if (((*data)->next)->exit_code == 1)
	{
		printf("minishell: syntax error near unexpected token `newline'\n");
		(*data) = head_data;
		(*data)->exit_code = 2;
		g_exit_code = 2;
		return (1);
	}
	if ((*data)->next == head_data)
	{
		printf("minishell: syntax error near unexpected token `newline'\n");
		(*data) = head_data;
		(*data)->exit_code = 2;
		g_exit_code = 2;
		return (1);
	}
	return (0);
}

/**
  * Removes an element data from a linked list while also updating the head and
  * pipe pointers
  * @param t_data.**data
  * @param t_data.**head
  * @param t_data.**pipe
  * @returns void
  */
static char	**ft_delete(t_data **data, t_data **head, t_data **pipe)
{
	char	**s;

	if ((*data) == *head)
		*head = (*data)->next;
	if (*pipe == *data)
		*pipe = (*data)->next;
	ft_delete_element(data);
	s = ft_split((*data)->content, "\f\t\n\r\v ");
	return (s);
}

/**
  * Removes an element data from a linked list while also updating the head and
  * pipe pointers
  * @param t_data.**data
  * @param t_data.**head
  * @param t_data.**pipe
  * @returns int
  */
static int	ft_delete2(t_data **data, t_data **head, t_data **pipe)
{
	if ((*data) == *head)
		*head = (*data)->next;
	if (*pipe == *data)
		*pipe = (*data)->next;
	ft_delete_element(data);
	if (*data == *head)
		return (0);
	return (1);
}

/**
  * Modifies the content of t_data structure by extracting a substring starting
  * after a specified prefix string and updates the content with the extracted
  * substring
  * @param t_data.**data
  * @param t_data.**head
  * @param char.**s
  * @returns void
  */
static void	ft_extract_s(t_data **data, char **s)
{
	char	*temp;

	temp = NULL;
	temp = ft_substr((*data)->content, ft_strlen(s[0]) + 1, \
		ft_strlen((*data)->content) - ft_strlen(s[0]) + 1);
	free((*data)->content);
	(*data)->content = ft_strdup(temp);
	free(temp);
}

/**
  * Processes and handles redirections in a command by copying valid redirection
  * tokens, modifying the linked list of data elements, and adding them to a
  * command's redirection list
  * @param t_data.**head
  * @param t_data.**data
  * @param t_cmd.*cmd
  * @param t_data.**pipe
  * @returns int
  */
int	ft_redirec(t_data **head, t_data **data, t_cmd *cmd, t_data **pipe)
{
	char	**s;
	int		j;

	if ((*data)->token != 5)
	{
		if (ft_invalid_redirec(data, *head))
			return (0);
		addlast_node(&(cmd->redirections), ft_data_copy(*data));
		s = ft_delete(data, head, pipe);
		addlast_node(&(cmd->redirections), ft_new_stack(ft_strdup(s[0]), NULL));
		j = ft_count_words((*data)->content, "\f\t\n\r\v ");
		if (j == 1)
		{
			if (!ft_delete2(data, head, pipe))
			{
				ft_free_split(s, j);
				return (2);
			}
		}
		else
			ft_extract_s(data, s);
		ft_free_split(s, j);
	}
	return (1);
}
