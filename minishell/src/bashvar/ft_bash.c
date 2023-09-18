/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bash.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thibnguy <thibnguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 17:39:51 by thibnguy          #+#    #+#             */
/*   Updated: 2023/09/18 19:58:44 by thibnguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_bash(t_bashvar **bash, char **envp)
{
	int	test;
	int	i;
	int	j;

	test = 0;
	i = 0;
	while (envp[i])
		i++;
	(*bash)->envp = (char **)malloc(sizeof(char *) * (i + 1));
	if (!(*bash)->envp)
		return ;
	i = -1;
	j = -1;
	while (envp[++i])
	{
		((*bash)->envp)[++j] = ft_strdup(envp[i]);
		// Si on est dans la ligne de PWD on remplit notre variable pwd
		if (ft_strncmp(envp[i], "PWD=", 4) == 0)
		{
			(*bash)->pwd = ft_substr(envp[i], 4, ft_strlen(envp[i]) - 4);
			test++;
		}
		else if (ft_strncmp(envp[i], "OLDPWD=", 7) == 0)
		{
			(*bash)->old_pwd = ft_substr(envp[i], 7, ft_strlen(envp[i]) - 7);
			test++;
		}
		if (test == 2)
			break ;
	}
	printf("old path : %s\n", (*bash)->old_pwd);
	printf("path : %s\n", (*bash)->pwd);
}
