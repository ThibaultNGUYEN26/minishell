/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lexer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thibnguy <thibnguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 19:53:32 by thibnguy          #+#    #+#             */
/*   Updated: 2023/08/21 14:19:06 by thibnguy         ###   ########.fr       */
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
		if (data->content != NULL && (ft_strchr(data->content, '\'') != -1 || ft_strchr(data->content, '\"') != -1) && data->exit_code != 2)
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
