/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thibnguy <thibnguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 17:18:55 by thibnguy          #+#    #+#             */
/*   Updated: 2023/10/11 22:14:22 by thibnguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	ft_delete(char *unset_value, t_bashvar **bash, int i)
{
	free((*bash)->envp[i]);
	(*bash)->envp[i] = NULL;
	while ((*bash)->envp[i + 1] != NULL)
	{
		(*bash)->envp[i] = ft_strdup((*bash)->envp[i + 1]);
		free((*bash)->envp[i + 1]);
		(*bash)->envp[i + 1] = NULL;
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

static int	ft_check_value(char *command)
{
	int	i;

	i = -1;
	while (command[++i])
		if (!ft_isalnum(command[i]) && command[i] != '_')
			return (0);
	return (1);
}

int	ft_unset(t_cmd *cmd, t_bashvar **bash)
{
	int		i;
	int		j;
	int		k;
	char	*str;
	int		test;
	int		exit_code_test;
	char	*unset_value;
	
	k = 0;
	str = NULL;
	i = -1;
	exit_code_test = 0;
	while (cmd->command[++k])
	{
		if (cmd->command[k] && cmd->command[k][0] == '-' && cmd->command[k][1] != '\0')
		{
			str = ft_strjoin(ft_strdup("minishell: unset: -"), ft_substr(cmd->command[k], 1, 1));
			str = ft_strjoin(str, ft_strdup(": invalid option\n"));
			ft_putstr_fd(str, 2);
			free(str);
			return (2);
		}
		if (!ft_check_value(cmd->command[k]))
		{
			str = ft_strjoin(ft_strdup("minishell: unset: `"), ft_substr(cmd->command[k], 0, ft_strlen(cmd->command[k])));
			str = ft_strjoin(str, ft_strdup("': not a valid identifier\n"));
			ft_putstr_fd(str, 2);
			free(str);
			exit_code = 1;
			exit_code_test = 1;
			continue ;
		}
		i = -1;
		unset_value = cmd->command[k];
		while ((*bash)->envp[++i])
		{
			test = 0;
			j = 0;
			while ((*bash)->envp[i][j])
			{
				if ((*bash)->envp[i][j] == '=')
				{
					str = ft_substr((*bash)->envp[i], 0, j);
					if (ft_strncmp((*bash)->envp[i], unset_value, j) == 0)
					{
						ft_delete(unset_value, bash, i);
						test = 1;
						if (!exit_code_test)
							exit_code = 0;
					}
					free(str);
					break ;
				}
				j++;
			}
			if (test == 1)
				break ;
		}
	}
	return (exit_code);
}