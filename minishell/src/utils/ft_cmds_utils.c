/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cmds_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchbouki <rchbouki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 20:41:26 by thibnguy          #+#    #+#             */
/*   Updated: 2023/09/06 15:01:44 by rchbouki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
  * Malloc a linked list.
  * @param content 
  * @param token
  * @returns new
  */
t_cmd	*ft_new_cmd()
{
	t_cmd	*new;

	new = malloc(sizeof(t_cmd) * 1);
	if (!new)
		return (NULL);
	new->redirections = NULL;
	new->next = new;
	new->prev = new;
	return (new);
}

/**
  * Add element at end of linked list.
  * @param stack
  * @param new_data
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
  * @param void 
  * @returns data
  */
void	ft_free_cmd(t_cmd *cmd)
{
	t_cmd	*head;

	head = cmd;
	if (cmd->next == cmd)
	{
		free(cmd);
		return ;
	}
	cmd = cmd->next;
	while (cmd != head)
	{
		cmd = cmd->next;
		free(cmd->prev);
	}
	free(cmd);
}

/**
  * Print linked list.
  * @param void
  * @returns data
  */
void	ft_print_cmd(t_cmd *cmd)
{
	t_cmd	*head;
	int		i;
	int		j;

	head = cmd;
	i = 0;
	while (1)
	{
		// print l'element
		printf("[%d]	:\n", i);
		j = 0;
		// print la commande en tableaux 2D
		printf("[command] : {");
		while (cmd->command[j])
			printf("%s , ", cmd->command[j++]);
		printf("}\n[redirection] : \n");
		ft_print_data(cmd->redirections);
		if ((cmd)->next == head)
			break;
		cmd = (cmd)->next;
		i++;
	}
	cmd = head;
}
