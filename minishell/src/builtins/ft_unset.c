/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thibnguy <thibnguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 17:18:55 by thibnguy          #+#    #+#             */
/*   Updated: 2023/09/20 04:28:52 by thibnguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	ft_delete(char *unset_value, t_bashvar **bash, int i)
{
	free((*bash)->envp[i]);
	while ((*bash)->envp[i])
	{
		(*bash)->envp[i] = NULL;
		if ((*bash)->envp[i + 1] == NULL)
		{
			free((*bash)->envp[i]);
			(*bash)->envp[i] = NULL;
		}
		else
		{
			free((*bash)->envp[i]);
			(*bash)->envp[i] = ft_strdup((*bash)->envp[i + 1]);
		}
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

int	ft_unset(t_cmd *cmd, t_bashvar **bash)
{
	int		i;
	int		j;
	int		k;
	int		test;
	char	**unset_value;
	
	k = 0;
	while (cmd->command[++k])
	{
		i = -1;
		unset_value = ft_split(cmd->command[k], "=");
		while ((*bash)->envp[++i])
		{
			test = 0;
			j = 0;
			while ((*bash)->envp[i][j])
			{
				if ((*bash)->envp[i][j] == '=')
				{
					if (ft_strcmp(unset_value[0], ft_substr((*bash)->envp[i], 0, j)) == 0)
					{
						ft_delete(unset_value[0], bash, i);
						test = 1;
					}
					break ;
				}
				j++;
			}
			if (test == 1)
				break ;
		}
		i = 0;
		while (unset_value[i])
			free(unset_value[i++]);
		free(unset_value);
	}
	return (EXIT_SUCCESS);
}