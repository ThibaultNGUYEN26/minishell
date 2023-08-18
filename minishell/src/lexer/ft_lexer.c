/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lexer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchbouki <rchbouki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 19:53:32 by thibnguy          #+#    #+#             */
/*   Updated: 2023/08/18 10:53:58 by rchbouki         ###   ########.fr       */
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
t_data	*ft_lexer(char *input, char **envp)
{
	int		i;
    int     j;
	t_data	*data;

	i = -1;
	data = NULL;
    (void)(envp);
	while (++i < ft_strlen(input))
	{
        // j commence initialement à i
        j = i;
        // Tant qu'on est pas à token ou que la chaine existe, on incrémente j
        while (!ft_tokenizer(input, j) && input[j])
            j++;
        // si on est au premier caractere, il y'a un token at the very start
        // sinon, on mets tout ce qu'il y avait avant dans data->content
        if (j != 0)
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
	ft_print_data(data);
	return (data);
}
