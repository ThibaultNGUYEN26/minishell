/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dollar_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thibnguy <thibnguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 22:59:20 by thibnguy          #+#    #+#             */
/*   Updated: 2023/10/14 19:11:20 by thibnguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
	* Checks if a character is a dollar sign
	* @param char.c
	* @param char.**res
	* @param int.i
	* @returns int
	*/
int	ft_check_dollar(char c, char **res, int i)
{
	char	*temp;

	temp = NULL;
	if (c == '$')
	{
		temp = ft_strdup("$");
		*res = ft_strjoin(*res, temp);
		i++;
	}
	return (i);
}

/**
	* Copies characters until it encounters a space, ', ", or '$'
	* @param int.*i
	* @param int.*j
	* @param t_data.*data
	* @param char.**res
	* @returns int
	*/
int	ft_norminette(int *i, int *j, t_data *data, char **res)
{
	*j = ft_strchr(data->content + *i, '$') + *i + 1;
	if (*i != 0)
		*res = ft_strjoin(*res, ft_substr(data->content + *i, 0, *j - *i - 1));
	*i = *j;
	while (data->content[*i] && data->content[*i] != ' '
		&& data->content[*i] != '\'' && data->content[*i] != '\"'
		&& data->content[*i] != '$')
		*i += 1;
	if (*i == *j)
	{
		*res = ft_strjoin(*res, ft_substr(data->content, *j - 1, 1));
		return (1);
	}
	return (0);
}

/**
	* Initializes the parsing of a string for dollar signs
	* @param t_data.*data
	* @param int.*i
	* @param int.*j
	* @param char.**res
	* @returns void
	*/
void	ft_dollar_init(t_data *data, int *i, int *j, char **res)
{
	*i = 0;
	*j = ft_strchr(data->content, '$') + 1;
	*res = ft_substr(data->content, *i, *j - 1);
}

/**
	* Checks if the character at position j is a '?'
	* @param char.*data
	* @param char.**res
	* @param int.i
	* @param int.j
	* @returns int
	*/
int	ft_question_mark(char *data, char **res, int i, int j)
{
	if (data[j] == '?')
	{
		*res = ft_strjoin(*res, ft_substr(data, j - 1, \
			i - j + 1));
		return (1);
	}
	return (0);
}
