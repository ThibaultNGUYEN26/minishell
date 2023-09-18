/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thibnguy <thibnguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 17:18:40 by thibnguy          #+#    #+#             */
/*   Updated: 2023/09/18 22:43:08 by thibnguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	ft_replace(char **export_value, t_bashvar **bash)
{
	char	*res;
	int		len;
	int		i;

	i = -1;
	len = ft_strlen(export_value[0]);
	while ((*bash)->envp[++i])
	{
		if (ft_strncmp((*bash)->envp[i], export_value[0], len) == 0)
		{
			res = ft_strjoin2(ft_strdup(export_value[0]), "=");
			res = ft_strjoin2(res, export_value[1]);
			free((*bash)->envp[i]);
			(*bash)->envp[i] = ft_strdup(res);
			if (ft_strcmp(export_value[0], "PWD") == 0)
			{
				free((*bash)->pwd);
				(*bash)->pwd = ft_strdup(res);
			}
			else if (ft_strcmp(export_value[0], "OLDPWD") == 0)
			{
				free((*bash)->old_pwd);
				(*bash)->old_pwd = ft_strdup(res);
			}
			free(res);
			break ;
		}
	}
}

static void	ft_add(char *export_value, t_bashvar **bash)
{
	int		i;

	i = -1;
	while ((*bash)->envp[++i])
		;
	(*bash)->envp[i++] = ft_strdup(export_value);
	(*bash)->envp[i] = NULL;
}

int	ft_export(t_cmd *cmd, t_bashvar **bash)
{
	int		i;
	int		j;
	int		k;
	int		test;
	char	**export_value;
	
	/* Chercher dans env name : 
			- si tu trouves, tu vas remplacer avec value ce qu'il y'avait après le =
			- sinon on add name=value à la fin 
	*/
	/* il faut checker si PWD ou OLD_PWD ont été changés pour bash->pwd et bash->old_pwd */
	k = 0;
	while (cmd->command[++k])
	{
		i = -1;
		export_value = ft_split(cmd->command[k], "=");
		while ((*bash)->envp[++i])
		{
			test = 0;
			j = 0;
			while ((*bash)->envp[i][++j])
			{
				if ((*bash)->envp[i][j - 1] == '=')
				{
					if (ft_strcmp(export_value[0], ft_substr((*bash)->envp[i], 0, j - 1)) == 0)
						test = 1;
					break ;
				}
			}
			if (test == 1)
				break ;
		}
		if (test == 1)
			ft_replace(export_value, bash);
		else
			ft_add(cmd->command[k], bash);
		i = 0;
		while (export_value[i])
			free(export_value[i++]);
		free(export_value);
	}
	return (EXIT_SUCCESS);
}