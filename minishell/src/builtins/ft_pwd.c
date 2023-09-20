/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thibnguy <thibnguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 17:18:46 by thibnguy          #+#    #+#             */
/*   Updated: 2023/09/20 04:09:20 by thibnguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_pwd(t_cmd *cmd, t_bashvar **bash)
{
	int	i;

	i = 0;
	while (cmd->command[i])
		i++;
	if (i > 1)
	{
		printf("pwd: too many arguments\n");
		return (EXIT_FAILURE);
	}
	printf("%s\n", (*bash)->pwd);
	return (EXIT_SUCCESS);
}
