/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchbouki <rchbouki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 17:18:29 by thibnguy          #+#    #+#             */
/*   Updated: 2023/10/12 00:53:14 by rchbouki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_env(t_cmd *cmd, t_bashvar **bash)
{
	int		i;
	char	*str;

	(void)cmd;
	i = 0;
	str = NULL;
	if (cmd->command[1] && cmd->command[1][0] == '-')
	{
		str = ft_strjoin(ft_strdup("env: invalid option -- '"), ft_substr(cmd->command[1], 1, 1));
		str = ft_strjoin(str, ft_strdup("'\n"));
		ft_putstr_fd(str, 2);
		free(str);
		return (125);
	}
	else if (cmd->command[1])
	{
		str = ft_strjoin(ft_strdup("env: ‘"), ft_substr(cmd->command[1], 0, ft_strlen(cmd->command[1])));
		str = ft_strjoin(str, ft_strdup("’: Permission denied\n"));
		ft_putstr_fd(str, 2);
		free(str);
		return (126);
	}
	while ((*bash)->envp[i])
		printf("%s\n", (*bash)->envp[i++]);
	return (0);
}
