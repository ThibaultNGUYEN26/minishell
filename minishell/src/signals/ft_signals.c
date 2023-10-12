/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_signals.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thibnguy <thibnguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/23 15:56:05 by thibnguy          #+#    #+#             */
/*   Updated: 2023/10/12 23:20:23 by thibnguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	sigint_handler(int sig)
{
	(void)sig;
	g_exit_code = 130;
	rl_on_new_line();
	rl_replace_line("", 0);
	write(STDOUT_FILENO, "\n", 1);
	rl_redisplay();
}

static void	sigquit_handler(int sig)
{
	struct termios	sa;

	(void)sig;
	tcgetattr(STDIN_FILENO, &sa);
	sa.c_lflag &= ~ECHOCTL;
	tcsetattr(STDIN_FILENO, TCSANOW, &sa);
}

void	ft_heredoc_handler(int sig)
{
	(void)sig;
	rl_replace_line("", STDIN_FILENO);
	write(STDIN_FILENO, "\n", 1);
	rl_on_new_line();
	g_exit_code = 1;
	exit(1);
}

void	ft_signals(void)
{
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, sigquit_handler);
}
