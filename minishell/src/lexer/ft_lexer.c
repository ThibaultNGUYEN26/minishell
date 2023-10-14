/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lexer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thibnguy <thibnguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 19:53:32 by thibnguy          #+#    #+#             */
/*   Updated: 2023/10/14 12:00:42 by thibnguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
	* Define what token is.
	* @param char.*input
	* @param int.i
	* @returns int
	*/
static int	ft_tokenizer(char *input, int i)
{
	if (ft_strncmp(input + i, ">>", 2) == 0 || !ft_strncmp(input + i, "<<", 2))
		return (1);
	if (input[i] == '|' || input[i] == '<' || input[i] == '>')
		return (1);
	return (0);
}

/**
	* Add the token to data
	* @param t_data.**data
	* @param char.*input
	* @param char.*i
	* @returns void
	*/
static void	ft_add_token(t_data **data, char *input, int *i)
{
	char	*str;

	str = ft_substr(input, *i, 2);
	if (ft_strcmp(str, ">>") == 0 || ft_strcmp(str, "<<") == 0)
	{
		addlast_node(data, ft_new_stack(NULL, str));
		*i += 1;
	}
	else if (input[*i] == '|' || input[*i] == '<' || input[*i] == '>')
	{
		free(str);
		addlast_node(data, ft_new_stack(NULL, ft_substr(input, *i, 1)));
	}
}

/**
	* Define list where all keywords are stocked.
	* @param char.*input
	* @returns t_data *
	*/
t_data	*ft_lexer(char *input)
{
	int		i;
	int		j;
	t_data	*data;
	char	c;

	i = 0;
	data = NULL;
	while (i < ft_strlen(input))
	{
		j = i;
		while (input[j] && !ft_tokenizer(input, j) && input[j] != '\"'
			&& input[j] != '\'')
			j++;
		if (input[j] == '\'' || input[j] == '\"')
		{
			c = input[j];
			while (input[++j] != c)
				;
			j++;
			addlast_node(&data, ft_new_stack(ft_substr(input, i, j - i), NULL));
		}
		else if (input[i] && !ft_tokenizer(input, i))
		{
			if (ft_tokenizer(input, j) && (input[j - 1] == ' ' \
				|| input[j - 1] == '\n' || input[j - 1] == '\r' \
				|| input[j - 1] == '\t'))
				addlast_node(&data, ft_new_stack(ft_substr(input, i, j - i - 1) \
					, NULL));
			else
				addlast_node(&data, ft_new_stack(ft_substr(input, i, j - i), \
					NULL));
		}
		i = j;
		if (input[i] && ft_tokenizer(input, i))
		{
			ft_add_token(&data, input, &i);
			i++;
		}
		else if (!input[i])
			break ;
	}
	return (data);
}

void	ft_quotes(t_data *data)
{
	t_data	*head;
	int		i;
	int		j;
	char	*res;
	char	c;

	head = data;
	while (1)
	{
		res = ft_strdup("");
		if (data->token == 5 && (ft_strchr(data->content, '\'') != -1 \
			|| ft_strchr(data->content, '\"') != -1) && data->exit_code != 2)
		{
			i = 0;
			while ((data->content)[i])
			{
				j = i;
				while ((data->content)[i] != '\'' && (data->content)[i] != '\"' \
					&& (data->content)[i])
					i++;
				if (i != j)
				{
					if (i != 0 && (data->content)[i - 1] == '$')
						res = ft_strjoin(res, ft_substr(data->content, j, \
							i - j - 1));
					else
						res = ft_strjoin(res, ft_substr(data->content, j, \
							i - j));
				}
				if ((data->content)[i] == '\'' || (data->content)[i] == '\"')
				{
					c = (data->content)[i++];
					j = i;
					while ((data->content)[j] != c)
						j++;
					res = ft_strjoin(res, ft_substr(data->content, i, j - i));
					i = ++j;
				}
			}
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
