/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fill_data.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thibnguy <thibnguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 21:03:08 by thibnguy          #+#    #+#             */
/*   Updated: 2023/07/01 09:20:33 by thibnguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static t_data	*ft_new_stack(char *content)
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

static void	addlast_node(t_data **stack, t_data *new_data)
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

t_data	*ft_fill_data(char *input)
{
	t_data	*data;
	char	**tab;
	int		i;

	tab = NULL;
	data = NULL;
	tab = ft_split(input, " ");
	i = -1;
	while (tab[++i])
		addlast_node(&data, ft_new_stack(tab[i]));
	return (data);
}
