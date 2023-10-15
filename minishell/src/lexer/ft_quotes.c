/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_quotes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thibnguy <thibnguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 23:43:16 by thibnguy          #+#    #+#             */
/*   Updated: 2023/10/15 16:53:42 by thibnguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
  * Helps construct substrings and add them to the result by considering whether
  * the previous character is '$' when extracting content
  * @param int.*i
  * @param int.*j
  * @param t_data.**data
  * @param char.**res
  * @returns void
  */
static void	ft_additional_help(int *i, int *j, t_data **data, char **res)
{
	if (*i != 0 && ((*data)->content)[*i - 1] == '$')
		(*res) = ft_strjoin((*res), ft_substr((*data)->content, *j, \
			*i - *j - 1));
	else
		(*res) = ft_strjoin((*res), ft_substr((*data)->content, *j, \
			*i - *j));
}

/**
  * Assists in processing single and double quotes by finding the start and end
  * of quoted sections within the content and appending the unquoted content to
  * the result
  * @param int.*i
  * @param int.*j
  * @param t_data.*data
  * @param char.**res
  * @returns void
  */
static void	ft_quotes_utils(int *i, int *j, t_data *data, char **res)
{
	char	c;

	*j = *i;
	while ((data->content)[*i] != '\'' && (data->content)[*i] != '\"' \
		&& (data->content)[*i])
		*i += 1;
	if (*i != *j)
		ft_additional_help(i, j, &data, res);
	if ((data->content)[*i] == '\'' || (data->content)[*i] == '\"')
	{
		c = (data->content)[*i];
		*i += 1;
		*j = *i;
		while ((data->content)[*j] != c)
			*j += 1;
		(*res) = ft_strjoin((*res), ft_substr(data->content, *i, *j - *i));
		*j += 1;
		*i = *j;
	}
}

/**
  * Processes content within single and double quotes for data nodes with the
  * token '5' and updates the data's content to include the extracted content
  * without the quotes
  * @param t_data.*data
  * @returns void
  */
void	ft_quotes(t_data *data)
{
	t_data	*head;
	int		i;
	int		j;
	char	*res;

	head = data;
	while (1)
	{
		res = ft_strdup("");
		if (data->token == 5 && (ft_strchr(data->content, '\'') != -1 \
			|| ft_strchr(data->content, '\"') != -1) && data->exit_code != 2)
		{
			i = 0;
			while ((data->content)[i])
				ft_quotes_utils(&i, &j, data, &res);
			free(data->content);
			data->content = ft_strdup(res);
		}
		free(res);
		if ((data)->next == head)
			break ;
		data = (data)->next;
	}
	data = head;
}
