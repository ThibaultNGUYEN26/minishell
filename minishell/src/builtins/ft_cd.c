/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchbouki <rchbouki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 17:14:57 by thibnguy          #+#    #+#             */
/*   Updated: 2023/09/19 18:13:50 by rchbouki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	ft_replace(char *var, char *new, t_bashvar **bash)
{
	char	*res;
	int		len;
	int		i;

	i = -1;
	len = ft_strlen(var);
	while ((*bash)->envp[++i])
	{
		if (ft_strncmp((*bash)->envp[i], var, len) == 0)
		{
			res = ft_strjoin2(ft_strdup(var), new);
			free((*bash)->envp[i]);
			(*bash)->envp[i] = ft_strdup(res);
			free(res);
			break ;
		}
	}
}

int	ft_cd(t_cmd *cmd, t_bashvar **bash)
{
	/* Change bash->old_pwd with bash->pwd */
	free((*bash)->old_pwd);
	(*bash)->old_pwd = ft_strdup((*bash)->pwd);
	ft_replace("OLDPWD=", (*bash)->old_pwd, bash);
	/* Changes the current working directory of the calling process to cmd->command[1] */
	if (chdir(cmd->command[1]) != 0)
	{
		perror("chdir: ");
		return (EXIT_FAILURE);
	}
	/* Change bash->pwd with the current directory */
	if (!getcwd((*bash)->pwd, 1024))
	{
		perror("getcwd: ");
		return (EXIT_FAILURE);
	}
	ft_replace("PWD=", (*bash)->pwd, bash);
	return(EXIT_SUCCESS);
}