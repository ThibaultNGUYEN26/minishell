/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thibnguy <thibnguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 17:18:35 by thibnguy          #+#    #+#             */
/*   Updated: 2023/09/19 09:37:32 by thibnguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_exit(t_cmd *cmd, t_bashvar **bash)
{
	(void)bash;
	int	i;

	ft_putstr_fd("exit\n", STDERR_FILENO);
	i = 0;
	while (cmd->command[i])
		i++;
	if (i > 2)
	{
		ft_putstr_fd("minishell: exit: too many arguments\n", STDERR_FILENO);
		return (EXIT_FAILURE);
	}
	else if (cmd->command[1] && !ft_isalpha(cmd->command[1]))
	{
		ft_putstr_fd("minishell: exit: ", STDERR_FILENO);
		ft_putstr_fd(cmd->command[1], STDERR_FILENO);
		ft_putstr_fd(": numeric argument required\n", STDERR_FILENO);
		return (EXIT_FAILURE);
	}
	exit(EXIT_SUCCESS);
	return (EXIT_SUCCESS);
}