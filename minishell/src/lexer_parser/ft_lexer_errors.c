/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lexer_errors.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchbouki <rchbouki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/20 19:06:41 by rchbouki          #+#    #+#             */
/*   Updated: 2023/08/20 20:57:0 by rchbouki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_quotes_error(t_data *data)
{
	t_data	*head;
	int		i;
	char	c;

	head = data;
	while (1)
	{
		i = -1;
		data->exit_code = 0;
		if (data->token == 5)
		{
			while ((data->content)[++i])
			{
				if ((data->content)[i] == '\"' || (data->content)[i] == '\'')
				{
					c = (data->content)[i++];
					while ((data->content)[i] != c && (data->content)[i])
						i++;
					if (!(data->content)[i])
					{
						data->exit_code = 2;
						break ; 
					}
				}
			}
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
        if (data->content == NULL && data->token != 5 && data->token != 0)
		{
			// if there is nothing apres, there is a problem
			if (data->next == head)
				break ;
			data = (data)->next;
			// if there is a content, imagine its a token ? on va avoir des seg fault sur NULL
			if (data->content)
			{
				if (ft_strchr(data->content, '\\') >= 0 || ft_strchr(data->content, '/') >= 0 || ft_strchr(data->content, '*') >= 0 || ft_strchr(data->content, '?') >= 0 || ft_strchr(data->content, '\"') >= 0 || ft_strchr(data->content, '<') >= 0 || ft_strchr(data->content, '>') >= 0 || ft_strchr(data->content, '|') >= 0)
					data->exit_code = 3;
			}
		}
        if ((data)->next == head)
			break;
		data = (data)->next;
    }
    data = head;
}
