/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thibnguy <thibnguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 17:14:57 by thibnguy          #+#    #+#             */
/*   Updated: 2023/09/18 18:27:00 by thibnguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_cd(t_cmd *cmd)
{
	int	i;
	

	i = -1;
	/* Changing the process's current working directory to the specified
	directory asked for after using cd */
	while (++i)
		chdir(cmd->command[1][i]);
}
