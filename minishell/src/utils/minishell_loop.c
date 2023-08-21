/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_loop.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchbouki <rchbouki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 17:53:46 by thibnguy          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2023/08/21 17:47:17 by rchbouki         ###   ########.fr       */
=======
/*   Updated: 2023/08/21 19:32:27 by thibnguy         ###   ########.fr       */
>>>>>>> 2340271b605846fdf2a0b6e5449168e0aa802a90
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
  * Input catcher and run lexer
  * @param input
  * @param envp
  * @returns void
  */
static void	ft_catch_input(char *input, char **envp)
{
	t_data	*data;

	if (!input)
		ft_ctrl_d();
	else if (ft_strcmp(input, "exit") == 0)
		ft_exit(input);
	else if (ft_strcmp(input, "") == 0)
		return ;
	data = ft_lexer(input);
	ft_quotes_error(data);
	ft_quotes(data);
	ft_redirect_error(data);
<<<<<<< HEAD
=======
	ft_builtins(data, input);
>>>>>>> 2340271b605846fdf2a0b6e5449168e0aa802a90
	ft_dollar(data, envp);
	ft_print_data(data);
	ft_free_stack(data);
}

/**
  * Loop the user input and catch signals from it + history functionality.
  * @param envp
  * @returns void
  */
void	ft_minishell_loop(char **envp)
{
	char	*input;
	
	input = NULL;
	// disable_echo();
	// signal(SIGINT, ft_ctrl_c);
	while (1)
	{
		input = readline(PROMPT);
		add_history(input);
		ft_catch_input(input, envp);
		free(input);
		input = NULL;
	}
}
