/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fill_data.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thibnguy <thibnguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 17:25:44 by thibnguy          #+#    #+#             */
/*   Updated: 2023/08/17 17:51:44 by thibnguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
  * Fill linked list with the user input.
  * @param input
  * @returns data
  */
t_data	*ft_fill_data(char *input, char **envp)
{
	t_data	*data;
	t_token	*token;
	int		i;

	i = -1;
	data = NULL;
	while (++i < ft_strlen(input))
	{
		if (ft_strcmp(ft_substr(input, i, 2), ">>") == 0 || ft_strcmp(ft_substr(input, i, 2), "<<") == 0)
		{
			addlast_node(&data, ft_new_stack(NULL, ft_substr(input, i, 2)));
			i++;
		}
		else if (input[i] == '|' || input[i] == '<' || input[i] == '>')
			addlast_node(&data, ft_new_stack(NULL, input[i]));
		else
			addlast_node(&data, ft_new_stack(input[i], NULL));
	}
}