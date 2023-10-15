/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lexer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thibnguy <thibnguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 19:53:32 by thibnguy          #+#    #+#             */
/*   Updated: 2023/10/15 16:55:18 by thibnguy         ###   ########.fr       */
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
	* @param int.*i
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
	* Scans the input string for tokens, single and double quotes, and
	* constructs data nodes based on the extracted substrings and their
	* respective delimiters
	* @param t_data.**data
	* @param char.*input
	* @param int.*i
	* @param int.*j
	* @returns void
	*/
static void	ft_lexer_utils(t_data **data, char *input, int *i, int *j)
{
	char	c;

	*j = *i;
	while (input[*j] && !ft_tokenizer(input, *j) && input[*j] != '\"'
		&& input[*j] != '\'')
		(*j)++;
	if (input[*j] == '\'' || input[*j] == '\"')
	{
		c = input[*j];
		while (input[++(*j)] != c)
			;
		(*j)++;
		addlast_node(data, ft_new_stack(ft_substr(input, *i, *j - *i), NULL));
	}
	else if (input[*i] && !ft_tokenizer(input, (*i)))
	{
		if (ft_tokenizer(input, *j) && (input[*j - 1] == ' ' \
			|| input[*j - 1] == '\n' || input[*j - 1] == '\r' \
			|| input[*j - 1] == '\t'))
			addlast_node(data, ft_new_stack(ft_substr(input, *i, *j - *i - 1) \
				, NULL));
		else
			addlast_node(data, ft_new_stack(ft_substr(input, *i, *j - *i), \
				NULL));
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

	i = 0;
	data = NULL;
	while (i < ft_strlen(input))
	{
		ft_lexer_utils(&data, input, &i, &j);
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
