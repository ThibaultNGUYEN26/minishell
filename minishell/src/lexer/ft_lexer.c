/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lexer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thibnguy <thibnguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 19:53:32 by thibnguy          #+#    #+#             */
/*   Updated: 2023/07/01 09:37:52 by thibnguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_print_data(t_data *data)
{
	t_data *head = data;
	while (1)
	{
		printf("%s\n", (data)->content);
		if ((data)->next == head)
			break;
		data = (data)->next;
	}
	data = head;
}

t_data	*ft_lexer(char *input)
{
	t_data	*data;

	data = ft_fill_data(input);
	ft_print_data(data);
	return (data);
}
