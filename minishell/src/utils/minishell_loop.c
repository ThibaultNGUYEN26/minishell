/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_loop.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thibnguy <thibnguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 17:53:46 by thibnguy          #+#    #+#             */
/*   Updated: 2023/07/03 15:34:18 by thibnguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
  * Input catcher and run lexer
  * @param input
  * @returns void
  */
static void	ft_catch_input(char *input)
{
	t_data	*data;

	if (!input)
		ft_ctrl_d();
	else if (ft_strcmp(input, "exit") == 0)
		ft_exit(input);
	data = ft_lexer(input);
	ft_free_stack(data);
}

/**
  * Loop the user input and catch signals from it + history functionality.
  * @param void
  * @returns void
  */
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
