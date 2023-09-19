/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bash.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchbouki <rchbouki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 17:39:51 by thibnguy          #+#    #+#             */
/*   Updated: 2023/09/19 18:25:38 by rchbouki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_bash(t_bashvar **bash, char **envp)
{
	int	i;
	int	j;

	i = 0;
	while (envp[i])
		i++;
	(*bash)->envp = (char **)malloc(sizeof(char *) * (i + 1));
	if (!(*bash)->envp)
		return ;
	i = -1;
	j = 0;
	while (envp[++i])
	{
		((*bash)->envp)[j++] = ft_strdup(envp[i]);
		// Si on est dans la ligne de PWD on remplit notre variable pwd
		if (ft_strncmp(envp[i], "PWD=", 4) == 0)
			(*bash)->pwd = ft_substr(envp[i], 4, ft_strlen(envp[i]) - 4);
		else if (ft_strncmp(envp[i], "OLDPWD=", 7) == 0)
			(*bash)->old_pwd = ft_substr(envp[i], 7, ft_strlen(envp[i]) - 7);
	}
	((*bash)->envp)[j] = NULL;
}

void	ft_free_bash(t_bashvar **bash)
{
	int	i;

	i = 0;
	while ((*bash)->envp[i])
		free((*bash)->envp[i++]);
	free((*bash)->envp);
	free((*bash)->pwd);
	free((*bash)->old_pwd);
	free((*bash));
}
