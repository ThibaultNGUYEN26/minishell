/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtins.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thibnguy <thibnguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 17:33:45 by thibnguy          #+#    #+#             */
/*   Updated: 2023/10/14 15:50:53 by thibnguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
  * Returns a pointer to a builtin function
  * @param char.*command
  * @returns int
  */
static int	(*ft_builtins_status(char *command))(t_cmd *cmd, t_bashvar **bash)
{
	if (command)
	{
		if (ft_strcmp(command, "cd") == 0)
			return (ft_cd);
		else if (ft_strcmp(command, "echo") == 0)
			return (ft_echo);
		else if (ft_strcmp(command, "env") == 0)
			return (ft_env);
		else if (ft_strcmp(command, "export") == 0)
			return (ft_export);
		else if (ft_strcmp(command, "pwd") == 0)
			return (ft_pwd);
		else if (ft_strcmp(command, "unset") == 0)
			return (ft_unset);
		else if (ft_strcmp(command, "exit") == 0)
			return (ft_exit);
		else if (ft_strcmp(command, "thibnguy") == 0)
			return (ft_thibnguy);
		else
			return (NULL);
	}
	else
		return (NULL);
}

/**
  * Put the result of ft_builtins_status in cmd structure
  * @param t_cmd.*cmd
  * @param t_bashvar.**bash
  * @returns void
  */
void	ft_builtin(t_cmd *cmd, t_bashvar **bash)
{
	t_cmd	*head;

	head = cmd;
	cmd->builtin = NULL;
	while (1)
	{
		if (cmd->command)
			cmd->builtin = ft_builtins_status((cmd->command)[0]);
		if (cmd->next == head)
		{
			cmd = cmd->next;
			break ;
		}
		cmd = cmd->next;
	}
	(void)bash;
}
