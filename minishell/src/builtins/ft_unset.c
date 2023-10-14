/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thibnguy <thibnguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 17:18:55 by thibnguy          #+#    #+#             */
/*   Updated: 2023/10/14 11:47:06 by thibnguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
  * Removes an environment variable from the bash structure
  * @param char.*unset_value
  * @param t_bashvar.**bash
  * @param int.i
  * @returns void
  */
static void	ft_delete(char *unset_value, t_bashvar **bash, int i)
{
	free((*bash)->envp[i]);
	(*bash)->envp[i] = NULL;
	while ((*bash)->envp[i + 1] != NULL)
	{
		(*bash)->envp[i] = ft_strdup((*bash)->envp[i + 1]);
		free((*bash)->envp[i + 1]);
		(*bash)->envp[i + 1] = NULL;
		i++;
	}
	if (ft_strcmp(unset_value, "PWD") == 0)
	{
		free((*bash)->pwd);
		(*bash)->pwd = ft_strdup("");
	}
	else if (ft_strcmp(unset_value, "OLDPWD") == 0)
	{
		free((*bash)->old_pwd);
		(*bash)->old_pwd = ft_strdup("");
	}
}

/**
  * Checks if the command has a valid environment variable name
  * @param char.*command
  * @returns int
  */
static int	ft_check_value(char *command)
{
	int		i;
	char	*str;

	i = -1;
	str = NULL;
	while (command[++i])
	{
		if (!ft_isalnum(command[i]) && command[i] != '_')
		{
			str = ft_strjoin(ft_strdup("minishell: unset: `"), \
				ft_substr(command, 0, ft_strlen(command)));
			str = ft_strjoin(str, ft_strdup("': not a valid identifier\n"));
			ft_putstr_fd(str, 2);
			free(str);
			g_exit_code = 1;
			return (0);
		}
	}
	return (1);
}

/**
  * Checks if the command has any options
  * @param char.*command
  * @returns int
  */
static int	ft_check_option(char *command)
{
	char	*str;

	str = NULL;
	if (command && command[0] == '-'
		&& command[1] != '\0')
	{
		str = ft_strjoin(ft_strdup("minishell: unset: -"), \
			ft_substr(command, 1, 1));
		str = ft_strjoin(str, ft_strdup(": invalid option\n"));
		ft_putstr_fd(str, 2);
		free(str);
		return (1);
	}
	return (0);
}

/**
  * Execute the unset command for a given variable name
  * @param t_cmd.*cmd
  * @param t_bashvar.**bash
  * @param int.*exit_code
  * @param int.k
  * @returns void
  */
static void	ft_exec_unset(t_cmd *cmd, t_bashvar **bash, int *exit_code, int k)
{
	int	i;
	int	j;

	i = -1;
	while ((*bash)->envp[++i])
	{
		j = 0;
		while ((*bash)->envp[i][j])
		{
			if ((*bash)->envp[i][j] == '=')
			{
				if (ft_strncmp((*bash)->envp[i], cmd->command[k], j) == 0)
				{
					ft_delete(cmd->command[k], bash, i);
					if (!exit_code)
						g_exit_code = 0;
				}
				break ;
			}
			j++;
		}
	}
}

/**
  * Removes environment variables from the bash structure
  * @param t_cmd.*cmd
  * @param t_bashvar.**bash
  * @returns int
  */
int	ft_unset(t_cmd *cmd, t_bashvar **bash)
{
	int		k;
	int		exit_code_test;

	k = 0;
	exit_code_test = 0;
	g_exit_code = 0;
	while (cmd->command[++k])
	{
		if (ft_check_option(cmd->command[k]))
			return (2);
		if (!ft_check_value(cmd->command[k]))
		{
			exit_code_test = 1;
			continue ;
		}
		ft_exec_unset(cmd, bash, &exit_code_test, k);
	}
	return (g_exit_code);
}
