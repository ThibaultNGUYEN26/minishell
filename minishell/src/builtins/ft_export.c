/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thibnguy <thibnguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 17:18:40 by thibnguy          #+#    #+#             */
/*   Updated: 2023/09/26 20:00:14 by thibnguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	ft_replace(char **export_value, t_bashvar **bash)
{
	char	*res;
	int		len;
	int		i;
	char	*str;

	i = -1;
	len = ft_strlen(export_value[0]);
	while ((*bash)->envp[++i])
	{
		if (ft_strncmp((*bash)->envp[i], export_value[0], len) == 0)
		{
			str = ft_strdup(export_value[0]);
			res = ft_strjoin2(str, "=");
			free(str);
			str = res;
			res = ft_strjoin2(str, export_value[1]);
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
			free(str);
			free(res);
			break ;
		}
	}
}

static void	ft_add(char *export_value, t_bashvar **bash)
{
	int		i;
	char	**temp;

	i = -1;
	while ((*bash)->envp[++i])
		;
	temp = malloc(sizeof(char *) * (i + 2));
	if (!temp)
		return ;
	i = -1;
	while ((*bash)->envp[++i])
		temp[i] = ft_strdup((*bash)->envp[i]);
	temp[i++] = ft_strdup(export_value);
	temp[i] = NULL;
	i = 0;
	while ((*bash)->envp[i])
		free((*bash)->envp[i++]);
	free((*bash)->envp);
	(*bash)->envp = temp;
}

int	ft_export(t_cmd *cmd, t_bashvar **bash)
{
	int		i;
	int		j;
	int		k;
	int		test;
	char	**export_value;
	char	*str;
	
	/* Chercher dans env name : 
			- si tu trouves, tu vas remplacer avec value ce qu'il y'avait après le =
			- sinon on add name=value à la fin 
	*/
	/* il faut checker si PWD ou OLD_PWD ont été changés pour bash->pwd et bash->old_pwd */
	k = 0;
	while (cmd->command[++k])
	{
		i = -1;
		if (cmd->command[k][0] == '=')
			printf("minishell: export: %s: not a valid identifier\n", cmd->command[k]);
		else
		{
			export_value = ft_split(cmd->command[k], "=");
			while ((*bash)->envp[++i])
			{
				test = 0;
				j = 0;
				while ((*bash)->envp[i][j])
				{
					if ((*bash)->envp[i][j] == '=')
					{
						str = ft_substr((*bash)->envp[i], 0, j);
						if (ft_strcmp(export_value[0], str) == 0)
							test = 1;
						free(str);
						break ;
					}
					j++;
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
	}
	return (EXIT_SUCCESS);
}