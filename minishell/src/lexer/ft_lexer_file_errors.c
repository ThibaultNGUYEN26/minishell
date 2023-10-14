/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lexer_file_errors.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thibnguy <thibnguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 18:37:03 by thibnguy          #+#    #+#             */
/*   Updated: 2023/10/14 18:55:35 by thibnguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
	* Check if character non valid in filename
	* @param t_data.*data
	* @returns int
	*/
static int	ft_check_filecharacters1(t_data *data)
{
	if (data->next->token != 5)
	{
		if (data->next->token == 0)
			ft_putstr_fd("minishell: syntax error near unexpected \
token '|'\n", 2);
		else if (data->next->token == 1)
			ft_putstr_fd("minishell: syntax error near unexpected \
token '<'\n", 2);
		else if (data->next->token == 2)
			ft_putstr_fd("minishell: syntax error near unexpected \
token '>'\n", 2);
		else if (data->next->token == 3)
			ft_putstr_fd("minishell: syntax error near unexpected \
token '>>'\n", 2);
		else if (data->next->token == 4)
			ft_putstr_fd("minishell: syntax error near unexpected \
token '<<'\n", 2);
		return (0);
	}
	else
	{
		ft_putstr_fd("minishell: syntax error near unexpected token \
'newline'\n", 2);
		return (0);
	}
	return (1);
}

/**
	* Check if character non valid in filename
	* @param t_data.*data
	* @returns int
	*/
static int	ft_check_filecharacters2(t_data *data)
{
	if (data->token != 5)
	{
		g_exit_code = 1;
		if (data->token == 0)
			ft_putstr_fd("minishell: syntax error near unexpected token '|'\
\n", 2);
		else if (data->token == 1)
			ft_putstr_fd("minishell: syntax error near unexpected token '<'\
\n", 2);
		else if (data->token == 2)
			ft_putstr_fd("minishell: syntax error near unexpected token '>'\
\n", 2);
		else if (data->token == 3)
			ft_putstr_fd("minishell: syntax error near unexpected token '>>'\
\n", 2);
		else if (data->token == 4)
			ft_putstr_fd("minishell: syntax error near unexpected token '<<'\
\n", 2);
		return (0);
	}
	return (1);
}

/**
	* Check if character non valid in filename
	* @param t_data.*data
	* @returns int
	*/
int	ft_check_filecharacters(t_data *data)
{
	if (data->content)
	{
		if (data->exit_code != 2)
		{
			if (ft_count_words(data->content, "\f\t\n\r\v ") == 0)
			{
				data->exit_code = 1;
				g_exit_code = 1;
				if (!ft_check_filecharacters1(data))
					return (1);
			}
		}
	}
	else if (!ft_check_filecharacters2(data))
		return (1);
	return (0);
}
