/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bash.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thibnguy <thibnguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 17:39:51 by thibnguy          #+#    #+#             */
/*   Updated: 2023/09/12 17:58:57 by thibnguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	ft_fill_bash(t_bashvar *bash, char **envp)
{
	int	i;
	int	j;

	i = -1;
	j = -1;
	bash->envp = malloc(sizeof(char **) * 1);
	if (!bash->envp)
		return ;
	while(envp[++i])
	{
		(bash->envp)[++j] = ft_strdup(envp[i]);
		// Si on est dans la ligne de PWD on remplit notre variable pwd
		if (ft_strncmp(envp[i], "PWD=", 4) == 0)
			bash->pwd = ft_substr(envp[i], 4, ft_strlen(envp[i]) - 4);
		else if (ft_strncmp(envp[i], "OLDPWD=", 7) == 0)
			bash->pwd = ft_substr(envp[i], 7, ft_strlen(envp[i]) - 7);
	}
}

void	ft_bash(t_bashvar *bash, char **envp)
{
	bash = malloc(sizeof(t_bashvar) * 1);
	if (!bash)
		return ;
	ft_fill_bash(bash, envp);
}
