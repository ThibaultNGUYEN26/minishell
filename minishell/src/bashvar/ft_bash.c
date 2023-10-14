/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bash.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thibnguy <thibnguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 17:39:51 by thibnguy          #+#    #+#             */
/*   Updated: 2023/10/14 18:30:13 by thibnguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
  * Sets envp, pwd and oldpwd to NULL
  * @param t_bashvar.**bash
  * @returns void
  */
static void	ft_set_null(t_bashvar **bash)
{
	((*bash)->envp) = NULL;
	(*bash)->pwd = NULL;
	(*bash)->old_pwd = NULL;
}

/**
  * Allocates bash->envp
  * @param t_bashvar.**bash
  * @param char.**envp
  * @returns void
  */
static int	ft_allocate_envp(t_bashvar **bash, char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
		i++;
	(*bash)->envp = (char **)malloc(sizeof(char *) * (i + 1));
	if (!(*bash)->envp)
		return (0);
	return (1);
}

/**
  * Initialize bash with environment variables and their values
  * @param t_bashvar.**bash
  * @param char.**envp
  * @returns void
  */
void	ft_bash(t_bashvar **bash, char **envp)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (*envp)
	{
		if (!ft_allocate_envp(bash, envp))
			return ;
		i = -1;
		while (envp[++i])
		{
			((*bash)->envp)[j++] = ft_strdup(envp[i]);
			if (ft_strncmp(envp[i], "PWD=", 4) == 0)
				(*bash)->pwd = ft_substr(envp[i], 4, ft_strlen(envp[i]) - 4);
			else if (ft_strncmp(envp[i], "OLDPWD=", 7) == 0)
				(*bash)->old_pwd = ft_substr(envp[i], 7, \
					ft_strlen(envp[i]) - 7);
		}
		((*bash)->envp)[j] = NULL;
	}
	else
		ft_set_null(bash);
}

/**
  * Free bash structure
  * @param t_bashvar.**bash
  * @returns void
  */
void	ft_free_bash(t_bashvar **bash)
{
	int	i;

	i = 0;
	if ((*bash)->envp)
	{
		while ((*bash)->envp[i])
			free((*bash)->envp[i++]);
		free((*bash)->envp);
		free((*bash)->pwd);
		(*bash)->pwd = NULL;
		free((*bash)->old_pwd);
		(*bash)->old_pwd = NULL;
	}
	if ((*bash)->pwd)
		free((*bash)->pwd);
	if ((*bash)->old_pwd)
		free ((*bash)->old_pwd);
	free((*bash));
}
