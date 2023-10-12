/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thibnguy <thibnguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 17:14:57 by thibnguy          #+#    #+#             */
/*   Updated: 2023/10/12 18:17:49 by thibnguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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

static int	ft_change_directory(t_cmd *cmd, t_bashvar **bash)
{
	free((*bash)->old_pwd);
	(*bash)->old_pwd = ft_strdup((*bash)->pwd);
	ft_replace_pwd("OLDPWD=", (*bash)->old_pwd, bash);
	if (chdir(cmd->command[1]) != 0)
	{
		printf("minishell: cd: %s: %s\n", cmd->command[1], strerror(errno));
		return (1);
	}
	if (!getcwd((*bash)->pwd, 4096))
		return (ft_exec_error("cd: "));
	ft_replace_pwd("PWD=", (*bash)->pwd, bash);
	return (0);
}

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
