/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ctrl.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thibnguy <thibnguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 13:34:27 by thibnguy          #+#    #+#             */
/*   Updated: 2023/09/08 18:34:49 by thibnguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
  * Print exit and shut down execution.
  * @param input 
  * @returns void
  */
void	ft_exit(char *input)
{
	printf("exit\n");
	free(input);
	exit(0);
}

void	ft_ctrl_d(void)
{
	printf("exit\n");
	exit(0);
}
