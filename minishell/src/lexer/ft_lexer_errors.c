/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lexer_errors.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchbouki <rchbouki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/20 19:06:41 by rchbouki          #+#    #+#             */
/*   Updated: 2023/08/20 19:17:59 by rchbouki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_quotes_error(t_data *data)
{
	int		i;
	int		count_double;
	int		count_simple;
	t_data	*head;

	head = data;
	while (1)
	{
		i = -1;
		count_double = 0;
		count_simple = 0;
		data->exit_code = 0;
		if (data->token == 5)
		{
			while ((data->content)[++i])
			{
				if ((data->content)[i] == '\"')
					count_double++;
				else if ((data->content)[i] == '\'')
					count_simple++;
			}
			if (count_double != 0 && count_double % 2 != 0)
				data->exit_code = 2;
			if (count_simple != 0 && count_simple % 2 != 0)
				data->exit_code = 2;
		}
		if ((data)->next == head)
			break;
		data = (data)->next;
	}
	data = head;
}

void    ft_redirect_error(t_data *data)
{
    t_data  *head;

    head = data;
    while (1)
    {
        
        if ((data)->next == head)
			break;
		data = (data)->next;
    }
    data = head;
}
