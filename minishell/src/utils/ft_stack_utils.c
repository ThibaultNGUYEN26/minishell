/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_stack_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchbouki <rchbouki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/01 09:59:21 by thibnguy          #+#    #+#             */
/*   Updated: 2023/08/18 10:56:25 by rchbouki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
  * Malloc a linked list.
  * @param content 
  * @param token
  * @returns new
  */
t_data	*ft_new_stack(char *content, char *token)
{
	t_data	*new;

	new = malloc(sizeof(t_data) * 1);
	if (!new)
		return (NULL);
	new->next = new;
	new->prev = new;
	new->content = content;
	if (token)
	{
		if (ft_strcmp(token, "|") == 0)
			new->token = PIPE;
		if (ft_strcmp(token, "<") == 0)
			new->token = INPUT;
		if (ft_strcmp(token, ">") == 0)
			new->token = OUTPUT;
		if (ft_strcmp(token, ">>") == 0)
			new->token = APPEND;
		if (ft_strcmp(token, "<<") == 0)
			new->token = HEREDOC;
	}
	else
		new->token = -1;
	return (new);
}

/**
  * Add element at end of linked list.
  * @param stack
  * @param new_data
  * @returns void
  */
void	addlast_node(t_data **stack, t_data *new_data)
{
	if (*stack == NULL)
	{
		*stack = new_data;
		(*stack)->next = *stack;
		(*stack)->prev = *stack;
		return ;
	}
	((*stack)->prev)->next = new_data;
	(new_data)->prev = (*stack)->prev;
	(new_data)->next = *stack;
	(*stack)->prev = new_data;
}

/**
  * Free linked list.
  * @param void 
  * @returns data
  */
void	ft_free_stack(t_data *data)
{
	t_data	*head;

	head = data;
	if (data->next == data)
	{
		free(data->content);
		free(data);
		return ;
	}
	data = data->next;
	while (data != head)
	{
		free(data->content);
		data = data->next;
		free(data->prev);
	}
	free(data->content);
	free(data);
}

/**
  * Print linked list.
  * @param void
  * @returns data
  */
void	ft_print_data(t_data *data)
{
	t_data	*head;
	int		i;

	head = data;
	i = 0;
	while (1)
	{
		printf("[%d] content : %s , token : %d\n", i, (data)->content, (data)->token);
		if ((data)->next == head)
			break;
		data = (data)->next;
		i++;
	}
	data = head;
}

