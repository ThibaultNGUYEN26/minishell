/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thibnguy <thibnguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 17:14:57 by thibnguy          #+#    #+#             */
/*   Updated: 2023/10/15 14:17:16 by thibnguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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
		str = ft_strjoin(ft_strdup("minishell: cd: -"), \
			ft_substr(command, 1, 1));
		str = ft_strjoin(str, ft_strdup(": invalid option\n"));
		ft_putstr_fd(str, 2);
		free(str);
		return (1);
	}
	return (0);
}

/**
  * Updates the environment variable that stores the current working directory
  * with new path
  * @param char.*var
  * @param char.*new
  * @param t_bashvar.**bash
  * @returns void
  */
static void	ft_replace_pwd(char *var, char *new, t_bashvar **bash)
{
	char	*res;
	int		len;
	int		i;
	char	*temp;

	i = -1;
	len = ft_strlen(var);
	while ((*bash)->envp[++i])
	{
		if (ft_strncmp((*bash)->envp[i], var, len) == 0)
		{
			temp = ft_strdup(var);
			res = ft_strjoin2(temp, new);
			free(temp);
			free((*bash)->envp[i]);
			(*bash)->envp[i] = ft_strdup(res);
			free(res);
			break ;
		}
	}
}

/**
  * Updates the environment variable with the previous working directory
  * @param t_bashvar.**bash
  * @returns void
  */
static void	ft_change_oldpwd(t_bashvar **bash)
{
	free((*bash)->old_pwd);
	(*bash)->old_pwd = ft_strdup((*bash)->pwd);
	ft_replace_pwd("OLDPWD=", (*bash)->old_pwd, bash);
}

/**
  * Changes the current working directory and update the PWD environment variable
  * with the new path
  * @param t_cmd.*cmd
  * @param t_bashvar.**bash
  * @returns int
  */
static int	ft_change_directory(t_cmd *cmd, t_bashvar **bash)
{
	if ((*bash)->envp)
		ft_change_oldpwd(bash);
	if (chdir(cmd->command[1]) != 0)
	{
		printf("minishell: cd: %s: %s\n", cmd->command[1], strerror(errno));
		return (1);
	}
	if ((*bash)->pwd)
		free((*bash)->pwd);
	(*bash)->pwd = malloc(sizeof(char) * 4096);
	if (!(*bash)->pwd)
		return (1);
	if (!getcwd((*bash)->pwd, 4096) || !(*bash)->pwd)
		return (free((*bash)->pwd), ft_exec_error("cd :"));
	if ((*bash)->envp)
		ft_replace_pwd("PWD=", (*bash)->pwd, bash);
	return (0);
}

/**
  * Checks special case like 'cd -' and calls ft_change_directory to change the
  * directory
  * @param t_cmd.*cmd
  * @param t_bashvar.**bash
  * @returns int
  */
int	ft_cd(t_cmd *cmd, t_bashvar **bash)
{
	int		i;

	i = 0;
	while (cmd->command[i])
		i++;
	if (cmd->command[1] && ft_strcmp(cmd->command[1], "-") == 0)
	{
		if (!cmd->command[1][1])
		{
			ft_pwd(cmd, bash);
			return (0);
		}
	}
	else if (ft_check_option(cmd->command[1]))
		return (2);
	if (i > 2)
	{
		printf("minishell: cd: too many arguments\n");
		return (1);
	}
	return (ft_change_directory(cmd, bash));
}
