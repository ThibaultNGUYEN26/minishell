/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_loop.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thibnguy <thibnguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 17:53:46 by thibnguy          #+#    #+#             */
/*   Updated: 2023/07/01 09:18:04 by thibnguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	ft_catch_input(char *input)
{
	if (!input)
		ft_ctrl_d();
	else if (ft_strcmp(input, "exit") == 0)
		ft_exit(input);
	ft_lexer(input);
}

void	ft_minishell_loop(void)
{
	char	*input;
	
	input = NULL;
	// disable_echo();
	// signal(SIGINT, ft_ctrl_c);
	while (1)
	{
		input = readline(GREEN PROMPT EOC);
		add_history(input);
		ft_catch_input(input);
		free(input);
		input = NULL;
	}
}
