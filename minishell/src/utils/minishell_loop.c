/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_loop.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thibnguy <thibnguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 17:53:46 by thibnguy          #+#    #+#             */
/*   Updated: 2023/06/27 19:31:48 by thibnguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	ft_catch_input(t_input *input)
{
	if (!input->content)
		ft_ctrl_d();
	else if (ft_strcmp(input->content, "exit") == 0)
		ft_exit(input);
}

void	ft_minishell_loop(void)
{
	t_input	*input;
	
	input = malloc(sizeof(t_input));
	if (!input)
		exit(1);
	// disable_echo();
	signal(SIGINT, ft_ctrl_c);
	while (1)
	{
		input->content = readline(PROMPT);
        if (input->content && *input->content)
            add_history(input->content);
		ft_catch_input(input);
		free(input->content);
		input->content = NULL;
	}
}
