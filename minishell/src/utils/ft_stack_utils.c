/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_stack_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thibnguy <thibnguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/01 09:59:21 by thibnguy          #+#    #+#             */
/*   Updated: 2023/07/01 10:01:29 by thibnguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_data	*ft_new_stack(char *content)
{
	t_data	*new;

	new = malloc(sizeof(t_data) * 1);
	if (!new)
		return (NULL);
	new->next = new;
	new->prev = new;
	new->content = content;
	return (new);
}

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