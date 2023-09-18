/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtins.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thibnguy <thibnguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 17:33:45 by thibnguy          #+#    #+#             */
/*   Updated: 2023/09/18 18:29:10 by thibnguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	(*ft_builtins_status(char *command))(t_cmd *cmd)
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
	else
		return (NULL);
}

int	ft_builtin(t_cmd *cmd)
{
	t_cmd	*head;

	head = cmd;
	while (1)
	{
		cmd->builtin = ft_builtins_status((cmd->command)[0]);
		if (cmd->next == head)
		{
			cmd = cmd->next;
			break ;
		}
		cmd = cmd->next;
	}
}
