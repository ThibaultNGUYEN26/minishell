/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thibnguy <thibnguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 16:41:46 by thibnguy          #+#    #+#             */
/*   Updated: 2023/10/14 14:54:37 by thibnguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
  * Checks if str contains "$?" and prints g_exit_code
  * @param char.**str
  * @param int.i
  * @param int.j
  * @returns int
  */
static int	ft_print_exit_code(char **str, int i, int j)
{
	char	*temp;

	if (ft_strncmp((str[i]) + j, "$?", 2) == 0)
	{
		temp = ft_itoa(g_exit_code);
		ft_putstr_fd(temp, STDOUT_FILENO);
		free(temp);
		return (1);
	}
	return (0);
}

/**
  * Called at the end of printing within the ft_print function
  * @param int.dollar
  * @param int.newline_var
  * @returns void
  */
static void	ft_end_print(int dollar, int newline_var)
{
	if (dollar == 1)
		g_exit_code = 0;
	if (newline_var == 0)
		ft_putstr_fd("\n", STDOUT_FILENO);
}

/**
  * Parses and prints str with a check for "$?" and handle -n option to suppress
  * the newline
  * @param char.**str
  * @param int.newline_var
  * @param int.i
  * @returns void
  */
static void	ft_print(char **str, int newline_var, int i)
{
	int		j;
	int		dollar;

	dollar = 0;
	while (str[i])
	{
		j = 0;
		while (str[i][j])
		{
			if (ft_print_exit_code(str, i, j))
			{
				j += 2;
				dollar = 1;
				continue ;
			}
			else
				ft_putchar_fd((str[i][j++]), STDOUT_FILENO);
		}
		i++;
		if (str[i])
			ft_putstr_fd(" ", STDOUT_FILENO);
	}
	ft_end_print(dollar, newline_var);
}

/**
  * Prints messages to the standard output
  * @param t_cmd.*cmd
  * @param t_bashvar.**bash
  * @returns int
  */
int	ft_echo(t_cmd *cmd, t_bashvar **bash)
{
	int	i;
	int	j;
	int	newline_var;

	j = 1;
	newline_var = 0;
	(void)bash;
	while (cmd->command[j] && cmd->command[j][0] == '-'
		&& cmd->command[j][1] == 'n')
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
	g_exit_code = 0;
	return (EXIT_SUCCESS);
}
