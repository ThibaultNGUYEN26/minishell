/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thibnguy <thibnguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 17:18:35 by thibnguy          #+#    #+#             */
/*   Updated: 2023/10/14 11:39:10 by thibnguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
  * Checks if the arguments are not numeric
  * @param char.*command
  * @returns int
  */
static int	ft_check_args(char *command)
{
	if ((ft_strcmp(command, "-1") != 0)
		&& (!ft_isnumeric(command) \
		|| ft_atoi(command) == -1))
	{
		ft_putstr_fd("minishell: exit: ", STDERR_FILENO);
		ft_putstr_fd(command, STDERR_FILENO);
		ft_putstr_fd(": numeric argument required\n", STDERR_FILENO);
		g_exit_code = 2;
		return (1);
	}
	return (0);
}

/**
  * Exit the program and calulates exit code % 256 for a long long sized argument
  * @param t_cmd.*cmd
  * @param t_bashvar.**bash
  * @returns int
  */
int	ft_exit(t_cmd *cmd, t_bashvar **bash)
{
	int	i;

	i = 0;
	ft_putstr_fd("exit\n", STDERR_FILENO);
	while (cmd->command[i])
		i++;
	if (i > 2)
	{
		ft_putstr_fd("minishell: exit: too many arguments\n", STDERR_FILENO);
		return (1);
	}
	if (i == 2)
	{
		if (!ft_check_args(cmd->command[1]))
		{
			if (cmd->command[1][0] == '-')
				g_exit_code = 256 + (ft_atoi(cmd->command[1]) % 256);
			else
				g_exit_code = ft_atoi(cmd->command[1]) % 256;
		}
	}
	ft_free_bash(bash);
	ft_free_cmd(cmd);
	exit(g_exit_code);
	return (EXIT_SUCCESS);
}
