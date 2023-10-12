/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thibnguy <thibnguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 17:18:46 by thibnguy          #+#    #+#             */
/*   Updated: 2023/10/12 18:48:35 by thibnguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	ft_check_option(char *command)
{
	char	*str;

	str = NULL;
	if (command && command[0] == '-'
		&& command[1] != '\0')
	{
		str = ft_strjoin(ft_strdup("minishell: pwd: -"), \
			ft_substr(command, 1, 1));
		str = ft_strjoin(str, ft_strdup(": invalid option\n"));
		ft_putstr_fd(str, 2);
		free(str);
		return (1);
	}
	return (0);
}

int	ft_pwd(t_cmd *cmd, t_bashvar **bash)
{
	char	*str;

	str = NULL;
	if (ft_check_option(cmd->command[1]))
		return (2);
	str = malloc(sizeof(char) * PATH_MAX);
	if (getcwd(str, (size_t)PATH_MAX) != NULL)
	{
		free((*bash)->pwd);
		(*bash)->pwd = ft_strdup(str);
		printf("%s\n", (*bash)->pwd);
	}
	else
	{
		free(str);
		exit(ft_exec_error("execve"));
	}
	free(str);
	return (0);
}
