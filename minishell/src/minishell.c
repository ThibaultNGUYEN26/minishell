/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thibnguy <thibnguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 17:52:08 by thibnguy          #+#    #+#             */
/*   Updated: 2023/06/17 20:57:58 by thibnguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	main(void)
{
	char	*input;

	ft_welcome();
	while (1)
	{
		input = readline(LIGHT_GREEN"minishell$> "EOC);
		if (input == NULL)
		{
			printf("Failed to read input.\n");
			return (1);
		}
		if (ft_strcmp(input, "exit") == 0)
			break ;
		free(input);
	}
	return (0);
}
