/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchbouki <rchbouki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 16:41:46 by thibnguy          #+#    #+#             */
/*   Updated: 2023/10/12 00:52:57 by rchbouki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	ft_print(char **str, int newline_var, int i)
{
	int		j;
	char	*temp;
	int		dollar;


	dollar = 0;
	while (str[i])
	{
		j = 0;
		while (str[i][j])
		{
			if (ft_strncmp((str[i]) + j, "$?", 2) == 0)
			{
				temp = ft_itoa(exit_code);
				ft_putstr_fd(temp, STDOUT_FILENO);
				free(temp);
				dollar = 1;
				j += 2;
			}
			else
			{
				ft_putchar_fd((str[i][j]), STDOUT_FILENO);
				j++;
			}
		}
		i++;
		if (str[i])
			ft_putstr_fd(" ", STDOUT_FILENO);
	}
	if (dollar == 1)
		exit_code = 0;
	if (newline_var == 0)
		ft_putstr_fd("\n", STDOUT_FILENO);
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
	ft_print(cmd->command, newline_var, j);
	exit_code = 0;
	return (EXIT_SUCCESS);
}
