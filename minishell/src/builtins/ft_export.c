/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thibnguy <thibnguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 17:18:40 by thibnguy          #+#    #+#             */
/*   Updated: 2023/10/14 18:24:08 by thibnguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
  * Checks if command is a valid environment variable key
  * @param char.*command
  * @returns int
  */
static int	ft_check_key(char *command)
{
	int	i;

	i = -1;
	if (command[0] == '=')
		return (0);
	while (command[++i] != '=')
		if (!ft_isalnum(command[i]) && command[i] != '_')
			return (0);
	return (1);
}

/**
  * Checks if the command has any options
  * @param char.*command
  * @returns int
  */
static int	ft_check_options(char *command)
{
	char	*str;

	str = NULL;
	if (command && command[0] == '-'
		&& command[1] != '\0')
	{
		str = ft_strjoin(ft_strdup("minishell: export: -"), \
			ft_substr(command, 1, 1));
		str = ft_strjoin(str, ft_strdup(": invalid option\n"));
		ft_putstr_fd(str, 2);
		free(str);
		return (1);
	}
	return (0);
}

/**
  * Checks if the command is a valid environment variable
  * @param char.*command
  * @returns int
  */
static int	ft_check_args(char *command)
{
	char	*str;

	str = NULL;
	if (!ft_check_key(command)
		&& ft_strchr(command, '=') != -1)
	{
		str = ft_strjoin(ft_strdup("minishell: export: `"), \
			ft_substr(command, 0, ft_strlen(command)));
		str = ft_strjoin(str, ft_strdup("': not a valid identifier\n"));
		ft_putstr_fd(str, 2);
		free(str);
		g_exit_code = 1;
		return (1);
	}
	return (0);
}

/**
  * Compares the keys of environment variables in the bash structure with a new
  * cmd and its associated export_value
  * @param t_bashvar.**bash
  * @param char.*cmd
  * @param int.i
  * @param char.**export_value
  * @returns void
  */
static void	ft_keycmp(t_bashvar **bash, char *cmd, int i, char **export_value)
{
	char	*str;
	int		j;

	str = NULL;
	if ((*bash)->envp)
	{
		while ((*bash)->envp[++i])
		{
			j = 0;
			while ((*bash)->envp[i][j])
			{
				if ((*bash)->envp[i][j] == '=')
				{
					str = ft_substr((*bash)->envp[i], 0, j);
					if (ft_strcmp(export_value[0], str) == 0)
						return (free(str), ft_replace(export_value, &bash));
					free(str);
					break ;
				}
				j++;
			}
		}
	}
	ft_add(cmd, &bash);
}

/**
  * Sets or modified environment variables
  * @param t_cmd.*cmd
  * @param t_bashvar.**bash
  * @returns int
  */
int	ft_export(t_cmd *cmd, t_bashvar **bash)
{
	int		i;
	int		j;
	char	**export_value;

	j = 0;
	if (ft_check_options(cmd->command[1]))
		return (2);
	while (cmd->command[++j])
	{
		i = -1;
		if (!ft_check_args(cmd->command[j]))
		{
			if (ft_strchr(cmd->command[j], '=') == -1)
				continue ;
			export_value = ft_split(cmd->command[j], "=");
			ft_keycmp(bash, cmd->command[j], i, export_value);
			i = 0;
			while (export_value[i])
				free(export_value[i++]);
			free(export_value);
		}
		else
			g_exit_code = 1;
	}
	return (g_exit_code);
}
