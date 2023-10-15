/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_quotes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thibnguy <thibnguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 23:43:16 by thibnguy          #+#    #+#             */
/*   Updated: 2023/10/14 23:50:13 by thibnguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	ft_quotes_utils(int *i, int *j, t_data *data, char **res)
{
	char	c;

	*j = *i;
	while ((data->content)[*i] != '\'' && (data->content)[*i] != '\"' \
		&& (data->content)[*i])
		(*i)++;
	if (*i != *j)
	{
		if (*i != 0 && (data->content)[*i - 1] == '$')
			(*res) = ft_strjoin((*res), ft_substr(data->content, *j, \
				*i - *j - 1));
		else
			(*res) = ft_strjoin((*res), ft_substr(data->content, *j, \
				*i - *j));
	}
	if ((data->content)[*i] == '\'' || (data->content)[*i] == '\"')
	{
		c = (data->content)[*i++];
		*j = *i;
		while ((data->content)[*j] != c)
			(*j)++;
		(*res) = ft_strjoin((*res), ft_substr(data->content, *i, *j - *i));
		*i = ++(*j);
	}
}

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
