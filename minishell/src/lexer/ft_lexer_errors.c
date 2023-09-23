/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lexer_errors.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thibnguy <thibnguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 18:15:00 by thibnguy          #+#    #+#             */
/*   Updated: 2023/09/23 15:16:25 by thibnguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
	* Check if there is unclosed quote
	* @param data
	* @param i
	* @returns void
	*/
static	void	ft_check_quotes(t_data *data, int i)
{
	char	c;

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
					printf("minishell: unexpected EOF while looking for matching `%c'\nminishell: syntax error: unexpected end of file\n", c);
					ft_free_stack(data);
					exit(2);
				}
			}
		}
	}
}

/**
	* Manage if there is unclosed quotes
	* @param data
	* @returns void
	*/
void	ft_quotes_error(t_data *data)
{
	t_data	*head;
	int		i;

	head = data;
	while (1)
	{
		i = -1;
		ft_check_quotes(data, i);
		if ((data)->next == head)
			break ;
		data = (data)->next;
	}
	data = head;
}

/**
	* Check if character non valid in filename
	* @param data
	* @returns void
	*/
static void	ft_check_filecharacters(t_data *data)
{
	if (data->content)
	{
		if (data->exit_code != 2)
		{
			if (ft_count_words(data->content, "\f\t\n\r\v ") == 0)
				data->exit_code = 1;
			else if (ft_strchr(data->content, '<') >= 0
				|| ft_strchr(data->content, '>') >= 0
				|| ft_strchr(data->content, '|') >= 0)
				data->exit_code = 1;
		}
	}
}

/**
	* Manage error when token is a redirection
	* @param data
	* @returns void
	*/
void	ft_redirect_error(t_data *data)
{
	t_data	*head;

	head = data;
	while (1)
	{
		if (data->content == NULL && data->token != 5 && data->token != 0)
		{
			// if there is nothing apres, there is a problem
			if (data->next == head)
				break ;
			data = (data)->next;
			if (data->token != 5)
				data->exit_code = 1;
			// if there is a content, imagine its a token ? on va avoir des seg 
			//fault sur NULL
			ft_check_filecharacters(data);
		}
		if ((data)->next == head)
			break ;
		data = (data)->next;
	}
	data = head;
}
