/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lexer_errors.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thibnguy <thibnguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 18:15:00 by thibnguy          #+#    #+#             */
/*   Updated: 2023/10/15 15:31:49 by thibnguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
	* Manages quotes in the input
	* @param char.*input
	* @returns int
	*/
int	ft_quotes_input(char *input)
{
	int		i;
	char	c;

	i = 0;
	while (input[i])
	{
		if (input[i] == '\"' || input[i] == '\'')
		{
			c = input[i++];
			while (input[i] != c && input[i])
				i++;
			if (!input[i])
			{
				printf("minishell: unexpected EOF while looking for matching `\
%c'\nminishell: syntax error: unexpected end of file\n", c);
				g_exit_code = 2;
				return (1);
			}
		}
		if (input[i])
			i++;
	}
	return (0);
}

/**
	* Check if there is unclosed quote
	* @param t_data.*data
	* @param int.i
	* @returns int
	*/
static	int	ft_check_quotes(t_data *data, int i)
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
					printf("minishell: unexpected EOF while looking for matching \
`%c'\nminishell: syntax error: unexpected end of file\n", \
						c);
					g_exit_code = 2;
					return (1);
				}
			}
		}
	}
	return (0);
}

/**
	* Manage if there is unclosed quotes
	* @param t_data.*data
	* @returns int
	*/
int	ft_quotes_error(t_data *data)
{
	t_data	*head;
	int		i;

	head = data;
	while (1)
	{
		i = -1;
		if (ft_check_quotes(data, i))
		{
			data = head;
			return (1);
		}
		if ((data)->next == head)
			break ;
		data = (data)->next;
	}
	data = head;
	return (0);
}

/**
	* Checks if input begins or finish with '|'
	* @param t_data.*data
	* @returns int
*/
static int	ft_check_token(t_data *data, t_data *head)
{
	if ((data->token == 0 && head == data) || (data->token == 0 \
		&& (data)->next == head))
	{
		ft_putstr_fd("minishell: syntax error near expected token `|'\n", 2);
		g_exit_code = 2;
		data = head;
		return (0);
	}
	return (1);
}

/**
	* Manage error when token is a redirection
	* @param t_data.*data
	* @returns int
*/
int	ft_redirect_error(t_data *data)
{
	t_data	*head;

	head = data;
	while (1)
	{
		if (data->content == NULL && data->token != 5 && data->token != 0)
		{
			if (data->next == head)
				break ;
			data = (data)->next;
			if (ft_check_filecharacters(data))
			{
				data = head;
				return (1);
			}
		}
		if (!ft_check_token(data, head))
			return (1);
		if ((data)->next == head)
			break ;
		data = (data)->next;
	}
	data = head;
	return (0);
}
