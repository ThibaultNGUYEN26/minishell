/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cmds_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thibnguy <thibnguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 20:41:26 by thibnguy          #+#    #+#             */
/*   Updated: 2023/10/15 16:36:38 by thibnguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
  * Malloc a linked list.
  * @param void
  * @returns t_cmd *
  */
t_cmd	*ft_new_cmd(void)
{
	t_cmd	*new;

	new = malloc(sizeof(t_cmd) * 1);
	if (!new)
		return (NULL);
	new->redirections = NULL;
	new->command = NULL;
	new->error = 0;
	new->next = new;
	new->prev = new;
	return (new);
}

/**
  * Add element at end of linked list.
  * @param t_cmd.**stack
  * @param t_cmd.**new_data
  * @returns void
  */
void	addlast_cmd(t_cmd **stack, t_cmd *new_cmd)
{
	if (*stack == NULL)
	{
		*stack = new_cmd;
		(*stack)->next = *stack;
		(*stack)->prev = *stack;
		return ;
	}
	((*stack)->prev)->next = new_cmd;
	(new_cmd)->prev = (*stack)->prev;
	(new_cmd)->next = *stack;
	(*stack)->prev = new_cmd;
}

/**
  * Free linked list.
  * @param t_cmd.*cmd
  * @returns void
  */
void	ft_free_cmd(t_cmd *cmd)
{
	t_cmd	*head;
	int		i;

	head = cmd;
	cmd = cmd->next;
	while (cmd != head)
	{
		i = 0;
		while (cmd->command && cmd->command[i])
			free(cmd->command[i++]);
		free(cmd->command);
		if (cmd->redirections)
			ft_free_stack(cmd->redirections);
		cmd = cmd->next;
		free(cmd->prev);
	}
	i = 0;
	while (cmd->command && cmd->command[i])
		free(cmd->command[i++]);
	free(cmd->command);
	if (cmd->redirections)
		ft_free_stack(cmd->redirections);
	free(cmd);
}
