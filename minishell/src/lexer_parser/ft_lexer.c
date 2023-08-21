/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lexer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchbouki <rchbouki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 19:53:32 by thibnguy          #+#    #+#             */
/*   Updated: 2023/08/21 19:57:39 by rchbouki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
	* Define what token is.
	* @param input
	* @param i
	* @returns int
	*/
int ft_tokenizer(char *input, int i)
{
	if (ft_strcmp(ft_substr(input, i, 2), ">>") == 0 || ft_strcmp(ft_substr(input, i, 2), "<<") == 0)
		return (1);
	if (input[i] == '|' || input[i] == '<' || input[i] == '>')
		return (1);
	return (0);
}

/**
	* Define list where all keywords are stocked.
	* @param input
	* @param envp
	* @returns data
	*/
t_data	*ft_lexer(char *input)
{
	int		i;
	int     j;
	t_data	*data;

	i = -1;
	data = NULL;
	while (++i < ft_strlen(input))
	{
		// j commence initialement à i
		j = i;
		// Tant qu'on est pas à token ou que la chaine existe, on incrémente j
		while (!ft_tokenizer(input, j) && input[j])
			j++;
		// si on est au premier caractere, il y'a un token at the very start
		// sinon, on mets tout ce qu'il y avait avant dans data->content
		if (!ft_tokenizer(input, i) && input[i])
			addlast_node(&data, ft_new_stack(ft_substr(input, i, j - i), NULL));
		i = j;
		// Si input existe toujours => on est arrivé au token, sinon y'a plus de tokens et we are at the end of the input
		if (input[i])
		{
			if (ft_strcmp(ft_substr(input, i, 2), ">>") == 0 || ft_strcmp(ft_substr(input, i, 2), "<<") == 0)
			{
				addlast_node(&data, ft_new_stack(NULL, ft_substr(input, i, 2)));
				i++;
			}
			else if (input[i] == '|' || input[i] == '<' || input[i] == '>')
				addlast_node(&data, ft_new_stack(NULL, ft_substr(input, i, 1)));
		}
		else
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
		// if it's not a token and there ARE quotes and they are well closed
		if (data->token == 5 && (ft_strchr(data->content, '\'') != -1 || ft_strchr(data->content, '\"') != -1) && data->exit_code != 2)
		{
			i = 0;
			while ((data->content)[i])
			{
				j = i;
				while ((data->content)[i] != '\'' && (data->content)[i] != '\"' && (data->content)[i])
					i++;
				// if the quote is not the first thing we encounter in content, we save in res what was before 
				if (i != j)
					res = ft_strjoin(res, ft_substr(data->content, j, i - j));
				// if we aren't at the end of content it means there are quotes
				if ((data->content)[i] == '\'' || (data->content)[i] == '\"')
				{
					c = (data->content)[i];
					i++;
					j = i;
					// find the next simple quote which closes
					while ((data->content)[j] != c)
						j++;
					// joining what we had of res and the quotes contenu without the quotes
					res = ft_strjoin(res, ft_substr(data->content, i, j - i));
					i = ++j;
				}
			}
			free(data->content);
			data->content = ft_strdup(res);
			free(res);
		}
		if ((data)->next == head)
			break;
		data = (data)->next;
	}
	data = head;
}

static char	*ft_dollar_utils(t_data *data, char **envp)
{
	char	*res;
	char	*dollar;
	int		j;
	int		i;
	
	i = 0;
	// get how many $ there are and save the last position
	j = ft_strchr(data->content, '$') + 1;
	// on met ce qu'il y avait avant le dollar dans res
	res = ft_substr(data->content, i, j - 1);
	while (data->content[i] && ft_strchr(data->content + i, '$') != -1)
	{
		j = ft_strchr(data->content + i, '$') + i + 1;
		i = j ;
		// i = jusqu'à où la variable $ va (exemple : $PATH' ici elle s'arrête à ')
		while (data->content[i] && data->content[i] != ' ' && data->content[i] != '\'' && data->content[i] != '\"' && data->content[i] != '$')
			i++;
		dollar = ft_substr(data->content, j, i - j);
		res = ft_substr(res, 0, ft_strchr(res, '$'));
		if (data->content[j] == '!' || data->content[j] == '@' || data->content[j] == '*' || (data->content[j] >= '0' && data->content[j] <= '9'))
			res = ft_strjoin(res, ft_substr(data->content, j + 1, ft_strlen(data->content) - j));
		else if (data->content[j] == '%' || data->content[j] == '^' || data->content[j] == '=' || data->content[j] == '+' || data->content[j] == '.' || data->content[j] == '/' || data->content[j] == ',')
			res = ft_strjoin(res, ft_substr(data->content, j, ft_strlen(data->content) - j));
		else if (data->content[j] == '#')
		{
			res = ft_strjoin(res, "0");
			res = ft_strjoin(res, ft_substr(data->content, j + 1, ft_strlen(data->content) - j));
		}
		else if (data->content[j] != '_')
		{
			j = 0;
			while (envp[j] && ft_strncmp(envp[j], dollar, ft_strchr(envp[j], '=')))
				j++;
			// if the envp exists we join it to res, sinon we just ignore it
			if (envp[j])
				res = ft_strjoin(res, envp[j] + ft_strlen(dollar) + 1);
		}
		free(dollar);
		// we add what was left of the word after the $
		res = ft_strjoin(res, ft_substr(data->content, i, ft_strlen(data->content)));
	}
	return (res);
}

void	ft_dollar(t_data *data, char **envp)
{
	t_data	*head;
	char	*res;

	head = data;
	while (1)
	{
		// si c'est un mot (donc not a token) et qu'il contient un $
		if (data->token == 5 && ft_strchr(data->content, '$') != -1)
		{
			res = ft_dollar_utils(data, envp);
			free(data->content);
			data->content = ft_strdup(res);
			free(res);
		}
		break ;
		if (data->next == head)
			break ;
		data = data->next;
	}
}
