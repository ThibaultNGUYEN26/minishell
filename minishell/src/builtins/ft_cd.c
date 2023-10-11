/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchbouki <rchbouki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 17:14:57 by thibnguy          #+#    #+#             */
/*   Updated: 2023/10/12 00:24:15 by rchbouki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	ft_replace(char *var, char *new, t_bashvar **bash)
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

int	ft_cd(t_cmd *cmd, t_bashvar **bash)
{
	int		i;
	char	*str;

	i = 0;
	str = NULL;
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
	else if (cmd->command[1] && cmd->command[1][0] == '-' && cmd->command[1][1] != '\0')
	{
		str = ft_strjoin(ft_strdup("minishell: cd: -"), ft_substr(cmd->command[1], 1, 1));
		str = ft_strjoin(str, ft_strdup(": invalid option\n"));
		ft_putstr_fd(str, 2);
		free(str);
		return (2);
	}
	if (i > 2)
	{
		printf("minishell: cd: too many arguments\n");
		return (1);
	}
	/* Change bash->old_pwd with bash->pwd */
	free((*bash)->old_pwd);
	(*bash)->old_pwd = ft_strdup((*bash)->pwd);
	ft_replace("OLDPWD=", (*bash)->old_pwd, bash);
	/* Changes the current working directory of the calling process to cmd->command[1] */
	if (chdir(cmd->command[1]) != 0)
	{
		printf("minishell: cd: %s: %s\n", cmd->command[1], strerror(errno));
		return (1);
	}
	/* Change bash->pwd with the current directory */
	if (!getcwd((*bash)->pwd, 4096))
		return(ft_exec_error("cd: "));
	ft_replace("PWD=", (*bash)->pwd, bash);
	return(0);
}
