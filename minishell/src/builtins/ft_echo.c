/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thibnguy <thibnguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 16:41:46 by thibnguy          #+#    #+#             */
/*   Updated: 2023/09/26 20:16:52 by thibnguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	ft_print(char **str, int output, int newline_var, int i)
{
	if (ft_strcmp(str[1], "$?") == 0)
	{
		printf("%d\n", exit_code);
		return ;
	}
	while (str[i])
	{
		ft_putstr_fd(str[i++], output);
		if (str[i])
			ft_putstr_fd(" ", output);
	}
	if (newline_var == 0)
		ft_putstr_fd("\n", output);
}

int	ft_echo(t_cmd *cmd, t_bashvar **bash)
{
	int	i;
	int	j;
	int	newline_var;

	i = 0;
	j = 1;
	newline_var = 0;
	(void)bash;
	if (cmd->command[1] && cmd->command[1][0] == '-')
	{
		while (cmd->command[1][++i] == 'n')
			;
		if (cmd->command[1][i] == '\0')
		{
			j++;
			newline_var = 1;
		}
	}
	ft_print(cmd->command, STDOUT_FILENO, newline_var, j);
	return (EXIT_SUCCESS);
}