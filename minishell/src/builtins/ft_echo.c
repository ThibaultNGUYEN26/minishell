/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thibnguy <thibnguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 16:41:46 by thibnguy          #+#    #+#             */
/*   Updated: 2023/10/07 18:47:54 by thibnguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	ft_print(char **str, int output, int newline_var, int i)
{
	if (ft_strcmp(str[1], "$?") == 0)
	{
		printf("%d\n", exit_code);
		exit_code = 0;
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

	j = 1;
	newline_var = 0;
	(void)bash;
	while (cmd->command[j] && cmd->command[j][0] == '-' && cmd->command[j][1] == 'n')
	{
		i = 0;
		while (cmd->command[j][++i] == 'n')
			;
		if (cmd->command[j][i] == '\0')
		{
			j++;
			newline_var = 1;
		}
		else
			break ;
	}
	ft_print(cmd->command, STDOUT_FILENO, newline_var, j);
	return (EXIT_SUCCESS);
}