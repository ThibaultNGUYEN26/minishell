/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ctrl.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thibnguy <thibnguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 13:34:27 by thibnguy          #+#    #+#             */
/*   Updated: 2023/07/03 15:18:46 by thibnguy         ###   ########.fr       */
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

/**
  * Get the current terminal settings and disable canonical mode and echoing
  * @param void 
  * @return void
  */
/* void	disable_echo(void) 
{
	struct termios term;

	// tcgetattr(STDIN_FILENO, &term);
	// term.c_lflag &= ~(ICANON | ECHO);
	// tcsetattr(STDIN_FILENO, TCSANOW, &term);

	tcgetattr(STDIN_FILENO, &term);
	term.c_lflag &= ~ICANON;    // non-canonical input 설정
	term.c_lflag &= ~ECHO;      // 입력 시 터미널에 보이지 않게
	term.c_cc[VMIN] = 1;        // 최소 입력 버퍼 크기
	term.c_cc[VTIME] = 0;       //버퍼 비우는 시간 (timeout)
	tcsetattr(STDIN_FILENO, TCSANOW, &term);

} */

void	ft_ctrl_d(void)
{
	printf("exit\n");
	exit(0);
}

/* void	ft_ctrl_c(int sig)
{
	(void)sig;
	write(STDOUT_FILENO, "\033[2D  \033[2D", 11);
	write(STDOUT_FILENO, "\n" PROMPT, \
		sizeof("\n" PROMPT) - 1);
} */

void	ft_ctrl_slash()
{
	
}
