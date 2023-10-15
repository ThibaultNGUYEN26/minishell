/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thibnguy <thibnguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 18:15:39 by thibnguy          #+#    #+#             */
/*   Updated: 2023/10/15 00:11:31 by thibnguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
  * Updates the PWD and OLDPWD values in the bash structure according to export
  * command
  * @param t_bashvar.***bash
  * @param char.*res
  * @param char.**export
  * @returns void
  */
static	void	ft_replace_pwd(t_bashvar ***bash, char *res, char **export)
{
	if (ft_strcmp(export[0], "PWD") == 0)
	{
		free((*(*bash))->pwd);
		(*(*bash))->pwd = ft_strdup(res);
	}
	else if (ft_strcmp(export[0], "OLDPWD") == 0)
	{
		free((*(*bash))->old_pwd);
		(*(*bash))->old_pwd = ft_strdup(res);
	}
}

/**
  * Replaces and existing environment variable in the bash structure
  * @param char.**export
  * @param t_bashvar.***bash
  * @returns void
  */
void	ft_replace(char **export, t_bashvar ***bash)
{
	char	*res;
	int		i;
	char	*str;

	i = -1;
	while ((*(*bash))->envp[++i])
	{
		if (!ft_strncmp((*(*bash))->envp[i], export[0], ft_strlen(export[0])))
		{
			str = ft_strdup(export[0]);
			res = ft_strjoin2(str, "=");
			if (export[1])
			{
				free(str);
				str = res;
				res = ft_strjoin2(str, export[1]);
			}
			free((*(*bash))->envp[i]);
			(*(*bash))->envp[i] = ft_strdup(res);
			ft_replace_pwd(bash, res, export);
			free(str);
			free(res);
			break ;
		}
	}
}

/**
  * Appends a new environment variable to a list of environment variable
  * @param t_bashvar.***bash
  * @param char.**temp
  * @param char.*export
  * @param int.*i
  * @returns void
  */
static void	ft_add_export(t_bashvar ***bash, char **temp, char *export)
{
	int	i;

	i = 0;
	temp = malloc(sizeof(char *) * 2);
	if (!temp)
		return ;
	temp[i++] = ft_strdup(export);
	temp[i] = NULL;
	(*(*bash))->envp = temp;
}

/**
  * Adds a new environment variable to the bash structure
  * @param char.*export_value
  * @param t_bashvar.***bash
  * @returns void
  */
void	ft_add(char *export_value, t_bashvar ***bash)
{
	int		i;
	char	**temp;

	i = -1;
	temp = NULL;
	if ((*(*bash))->envp)
	{
		while ((*(*bash))->envp[++i])
			;
		temp = malloc(sizeof(char *) * (i + 2));
		if (!temp)
			return ;
		i = -1;
		while ((*(*bash))->envp[++i])
			temp[i] = ft_strdup((*(*bash))->envp[i]);
		temp[i++] = ft_strdup(export_value);
		temp[i] = NULL;
		i = 0;
		while ((*(*bash))->envp[i])
			free((*(*bash))->envp[i++]);
		free((*(*bash))->envp);
		(*(*bash))->envp = temp;
	}
	else
		ft_add_export(bash, temp, export_value);
}
