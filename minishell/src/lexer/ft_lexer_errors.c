/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lexer_errors.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thibnguy <thibnguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 18:15:00 by thibnguy          #+#    #+#             */
/*   Updated: 2023/10/09 18:27:14 by thibnguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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
				printf("minishell: unexpected EOF while looking for matching `%c'\nminishell: syntax error: unexpected end of file\n", c);
				exit_code = 2;
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
	* @param data
	* @param i
	* @returns void
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
					printf("minishell: unexpected EOF while looking for matching `%c'\nminishell: syntax error: unexpected end of file\n", c);
					exit_code = 2;
					return (1);
				}
			}
		}
	}
	return (0);
}

/**
	* Manage if there is unclosed quotes
	* @param data
	* @returns void
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
	* Check if character non valid in filename
	* @param data
	* @returns void
	*/
static int	ft_check_filecharacters(t_data *data)
{
	if (data->content)
	{
		if (data->exit_code != 2)
		{
			if (ft_count_words(data->content, "\f\t\n\r\v ") == 0)
			{
				data->exit_code = 1;
				exit_code = 1;
				if (data->next->token != 5)
				{
					if (data->next->token == 0)
						ft_putstr_fd("minishell: syntax error near unexpected token '|'\n", 2);
					else if (data->next->token == 1)
						ft_putstr_fd("minishell: syntax error near unexpected token '<'\n", 2);
					else if (data->next->token == 2)
						ft_putstr_fd("minishell: syntax error near unexpected token '>'\n", 2);
					else if (data->next->token == 3)
						ft_putstr_fd("minishell: syntax error near unexpected token '>>'\n", 2);
					else if (data->next->token == 4)
						ft_putstr_fd("minishell: syntax error near unexpected token '<<'\n", 2);
				}
				else
					ft_putstr_fd("minishell: syntax error near unexpected token 'newline'\n", 2);
				return (1);
			}
		}
	}
	else
	{
		if (data->token != 5)
		{
			if (data->token == 0)
				ft_putstr_fd("minishell: syntax error near unexpected token '|'\n", 2);
			else if (data->token == 1)
				ft_putstr_fd("minishell: syntax error near unexpected token '<'\n", 2);
			else if (data->token == 2)
				ft_putstr_fd("minishell: syntax error near unexpected token '>'\n", 2);
			else if (data->token == 3)
				ft_putstr_fd("minishell: syntax error near unexpected token '>>'\n", 2);
			else if (data->token == 4)
				ft_putstr_fd("minishell: syntax error near unexpected token '<<'\n", 2);
			return (1);
		}
	}
	return (0);
}

/**
	* Manage error when token is a redirection
	* @param data
	* @returns void
	*/
int	ft_redirect_error(t_data *data)
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
			// if there is a content, imagine its a token ? on va avoir des seg 
			//fault sur NULL
			if (ft_check_filecharacters(data))
			{
				data = head;	
				return (1);
			}
		}
		if ((data->token == 0 && head == data) || (data->token == 0 && (data)->next == head))
		{
			ft_putstr_fd("minishell: syntax error near expected token `|'\n", 2);
			exit_code = 2;
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
