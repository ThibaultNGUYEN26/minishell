/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_signals.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thibnguy <thibnguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/23 15:56:05 by thibnguy          #+#    #+#             */
/*   Updated: 2023/10/15 13:25:38 by thibnguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
	* Gets or sets the value of a static boolean variable by providing a set
	* flag and value to assign to the variable, primarily used to manage a
	* persistent boolean state across function calls
	* @param bool set
	* @param bool value
	* @returns bool
	*/
bool	get_hd_bool(bool set, bool value)
{
	static bool	hd_bool = false;

	if (set)
		hd_bool = value;
	return (hd_bool);
}

/**
	* Signal handler for the SIGINT signal (ctrl+c)
	* @param int.sig
	* @returns void
	*/
void	sigint_handler(int sig)
{
	(void)sig;
	g_exit_code = 130;
	if (get_hd_bool(false, true))
		return ;
	rl_on_new_line();
	rl_replace_line("", 0);
	write(STDOUT_FILENO, "\n", 1);
	rl_redisplay();
}

/**
	* Signal handler for the SIGQUIT signal (ctrl+/)
	* @param int.sig
	* @returns void
	*/
static void	sigquit_handler(int sig)
{
	struct termios	sa;

	(void)sig;
	tcgetattr(STDIN_FILENO, &sa);
	sa.c_lflag &= ~ECHOCTL;
	tcsetattr(STDIN_FILENO, TCSANOW, &sa);
}

/**
	* Signal handler for the SIGINT signal inside a heredoc (ctrl+c)
	* @param int.sig
	* @returns void
	*/
void	ft_heredoc_handler(int sig)
{
	(void)sig;
	printf("\n");
	g_exit_code = 130;
	exit(g_exit_code);
}

/**
	* Uses signal function associate to handlers
	* @param void
	* @returns void
	*/
void	ft_signals(void)
{
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, sigquit_handler);
}
