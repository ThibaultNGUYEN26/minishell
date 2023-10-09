/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thibnguy <thibnguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 17:14:57 by thibnguy          #+#    #+#             */
/*   Updated: 2023/10/09 20:14:27 by thibnguy         ###   ########.fr       */
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
	int	i;

	i = 0;
	while (cmd->command[i])
		i++;
	if (i > 2)
	{
		exit_code = 1;
		printf("minishell: cd: too many arguments\n");
		return (EXIT_FAILURE);
	}
	if (!cmd->command[1])
		return (EXIT_SUCCESS);
	if (ft_strcmp(cmd->command[1], "-") == 0)
	{
		ft_pwd(cmd, bash);
		exit_code = 0;
		return (EXIT_SUCCESS);
	}
	/* Change bash->old_pwd with bash->pwd */
	free((*bash)->old_pwd);
	(*bash)->old_pwd = ft_strdup((*bash)->pwd);
	ft_replace("OLDPWD=", (*bash)->old_pwd, bash);
	/* Changes the current working directory of the calling process to cmd->command[1] */
	if (chdir(cmd->command[1]) != 0)
	{
		exit_code = 1;
		printf("minishell: cd: %s: %s\n", cmd->command[1], strerror(errno));
		return (EXIT_FAILURE);
	}
	/* Change bash->pwd with the current directory */
	if (!getcwd((*bash)->pwd, 4096))
	{
		exit_code = 1;
		perror("getcwd: ");
		return (EXIT_FAILURE);
	}
	ft_replace("PWD=", (*bash)->pwd, bash);
	exit_code = 0;
	return(EXIT_SUCCESS);
}
