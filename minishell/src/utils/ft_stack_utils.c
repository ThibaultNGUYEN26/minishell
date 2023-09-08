/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_stack_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchbouki <rchbouki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/01 09:59:21 by thibnguy          #+#    #+#             */
/*   Updated: 2023/09/08 20:47:46 by rchbouki         ###   ########.fr       */
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
	new->exit_code = 0;
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
		new->token = NONE;
	return (free(token), new);
}

/* Function returning a copy of the data passed as a paramater */
t_data	*ft_data_copy(t_data *data)
{
	t_data	*new_data;

	new_data = malloc(sizeof(t_data) * 1);
	if (!new_data)
		return (NULL);
	new_data->content = data->content;
	new_data->token = data->token;
	new_data->exit_code = data->exit_code;
	return (new_data);
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
  * Delete data from its linked list.
  * @param **data
  * @returns void
  */
void	ft_delete_element(t_data **data)
{
	// Si il ne reste plus qu'un seul element : on free data et data = NULL
	if ((*data) == (*data)->next)
	{
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
	data = NULL;
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
	while (1 && data)
	{
		printf("[%d] content : %s, token : %d, exit_code : %d\n", i, \
			(data)->content, (data)->token, (data)->exit_code);
		if ((data)->next == head)
			break ;
		data = (data)->next;
		i++;
	}
	data = head;
}
