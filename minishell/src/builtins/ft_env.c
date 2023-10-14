/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thibnguy <thibnguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 17:18:29 by thibnguy          #+#    #+#             */
/*   Updated: 2023/10/14 12:52:04 by thibnguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
  * Checks if the command has any options
  * @param char.*command
  * @returns int
  */
static int	ft_check_option(char *command)
{
	char	*str;

	str = NULL;
	if (command && command[0] == '-')
	{
		str = ft_strjoin(ft_strdup("env: invalid option -- '"), \
			ft_substr(command, 1, 1));
		str = ft_strjoin(str, ft_strdup("'\n"));
		ft_putstr_fd(str, 2);
		free(str);
		return (1);
	}
	return (0);
}

/**
  * Displays the environment variables
  * @param t_cmd.*cmd
  * @param t_bashvar.**bash
  * @returns int
  */
int	ft_env(t_cmd *cmd, t_bashvar **bash)
{
	int		i;
	char	*str;

	(void)cmd;
	i = 0;
	str = NULL;
	if (ft_check_option(cmd->command[1]))
		return (125);
	else if (cmd->command[1])
	{
		str = ft_strjoin(ft_strdup("env: ‘"), ft_substr(cmd->command[1], 0, \
			ft_strlen(cmd->command[1])));
		str = ft_strjoin(str, ft_strdup("’: Permission denied\n"));
		ft_putstr_fd(str, 2);
		free(str);
		return (126);
	}
	if ((*bash)->envp)
		while ((*bash)->envp[i])
			printf("%s\n", (*bash)->envp[i++]);
	return (0);
}
