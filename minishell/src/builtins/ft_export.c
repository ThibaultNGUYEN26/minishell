/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thibnguy <thibnguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 17:18:40 by thibnguy          #+#    #+#             */
/*   Updated: 2023/10/12 20:31:38 by thibnguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	ft_check_key(char *command)
{
	int	i;

	i = -1;
	if (command[0] == '=')
		return (0);
	while (command[++i] != '=')
		if (!ft_isalnum(command[i]) && command[i] != '_')
			return (0);
	return (1);
}

static int	ft_check_options(char *command)
{
	char	*str;

	str = NULL;
	if (command && command[0] == '-'
		&& command[1] != '\0')
	{
		str = ft_strjoin(ft_strdup("minishell: export: -"), \
			ft_substr(command, 1, 1));
		str = ft_strjoin(str, ft_strdup(": invalid option\n"));
		ft_putstr_fd(str, 2);
		free(str);
		return (1);
	}
	return (0);
}

static int	ft_check_args(char *command)
{
	char	*str;

	str = NULL;
	if (!ft_check_key(command)
		&& ft_strchr(command, '=') != -1)
	{
		str = ft_strjoin(ft_strdup("minishell: export: `"), \
			ft_substr(command, 0, ft_strlen(command)));
		str = ft_strjoin(str, ft_strdup("': not a valid identifier\n"));
		ft_putstr_fd(str, 2);
		free(str);
		g_exit_code = 1;
		return (1);
	}
	return (0);
}

static void	ft_keycmp(t_bashvar **bash, char *cmd, int i, char **export_value)
{
	char	*str;
	int		j;

	str = NULL;
	while ((*bash)->envp[++i])
	{
		j = 0;
		while ((*bash)->envp[i][j])
		{
			if ((*bash)->envp[i][j] == '=')
			{
				str = ft_substr((*bash)->envp[i], 0, j);
				if (ft_strcmp(export_value[0], str) == 0)
				{
					free(str);
					ft_replace(export_value, &bash);
					return ;
				}
				free(str);
				break ;
			}
			j++;
		}
	}
	ft_add(cmd, &bash);
}

int	ft_export(t_cmd *cmd, t_bashvar **bash)
{
	int		i;
	int		j;
	char	**export_value;

	j = 0;
	if (ft_check_options(cmd->command[1]))
		return (2);
	while (cmd->command[++j])
	{
		i = -1;
		if (!ft_check_args(cmd->command[j]))
		{
			if (ft_strchr(cmd->command[j], '=') == -1)
				continue ;
			export_value = ft_split(cmd->command[j], "=");
			ft_keycmp(bash, cmd->command[j], i, export_value);
			i = 0;
			while (export_value[i])
				free(export_value[i++]);
			free(export_value);
		}
		else
			g_exit_code = 1;
	}
	return (g_exit_code);
}
