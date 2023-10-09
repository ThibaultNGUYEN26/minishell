/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thibnguy <thibnguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 17:18:46 by thibnguy          #+#    #+#             */
/*   Updated: 2023/10/09 23:24:22 by thibnguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	ft_lp_errors(char *option)
{
	int	i;

	i = 1;
	if (option[0] == '-')
	{	
		while (option[i] == 'L' || option[i] == 'P')
			i++;
		if (!option[i])
			return (-1);
		else
			return (i);
	}
	return (-1);
}

int	ft_pwd(t_cmd *cmd, t_bashvar **bash)
{
	char	*str;
	char	*temp;
	int		i;

	if (cmd->command[1])
		i = ft_lp_errors(cmd->command[1]);
	else
		i = -1;
	str = NULL;
	temp = NULL;
	if (i != -1)
	{
		temp = ft_substr(cmd->command[1], i, 1);
		str = ft_strjoin2("minishell: pwd: -", temp);
		free(temp);
		temp = ft_strdup(": invalid option\n");
		str = ft_strjoin(str, temp);
		temp = ft_strdup("pwd: usage: pwd [-LP]\n");
		str = ft_strjoin(str, temp);
		ft_putstr_fd(str, 2);
		free(str);
		exit_code = 2;
		return (EXIT_FAILURE);
	}
	printf("%s\n", (*bash)->pwd);
	exit_code = 0;
	return (EXIT_SUCCESS);
}
