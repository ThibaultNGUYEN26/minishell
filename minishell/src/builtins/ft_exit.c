/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thibnguy <thibnguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 17:18:35 by thibnguy          #+#    #+#             */
/*   Updated: 2023/09/20 03:53:46 by thibnguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_exit(t_cmd *cmd, t_bashvar **bash)
{
	int	i;
	int	exit_code;

	i = 0;
	exit_code = 0;
	ft_putstr_fd("exit\n", STDERR_FILENO);
	while (cmd->command[i])
		i++;
	if (i > 2)
	{
		ft_putstr_fd("minishell: exit: too many arguments\n", STDERR_FILENO);
		return (EXIT_FAILURE);
	}
	else if ((ft_strcmp(cmd->command[1], "-1") != 0) && ((cmd->command[1] && !ft_isalpha(cmd->command[1])) || ft_atoi(cmd->command[1]) == -1))
	{
		ft_putstr_fd("minishell: exit: ", STDERR_FILENO);
		ft_putstr_fd(cmd->command[1], STDERR_FILENO);
		ft_putstr_fd(": numeric argument required\n", STDERR_FILENO);
		exit_code = 2;
	}
	else
	{
		if (cmd->command[1][0] == '-')
			exit_code = 256 + (ft_atoi(cmd->command[1]) % 256);
		else
			exit_code = ft_atoi(cmd->command[1]) % 256;
	}
	ft_free_bash(bash);
	ft_free_cmd(cmd);
	exit(exit_code);
	return (EXIT_SUCCESS);
}
