/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_signals.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thibnguy <thibnguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/23 15:56:05 by thibnguy          #+#    #+#             */
/*   Updated: 2023/09/23 16:20:10 by thibnguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	sigint_handler(int sig)
{
	rl_on_new_line();
	rl_replace_line("", 0);
	printf("\n");
	rl_redisplay();
	(void) sig;
}

void	ft_signals(void)
{
	signal(SIGINT, sigint_handler);
}