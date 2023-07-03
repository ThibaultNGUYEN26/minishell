/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lexer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thibnguy <thibnguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 19:53:32 by thibnguy          #+#    #+#             */
/*   Updated: 2023/07/03 14:51:34 by thibnguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/* t_token	*ft_tokenzier(t_data *data)
{
	
} */

t_data	*ft_lexer(char *input)
{
	t_data	*data;

	data = ft_fill_data(input);
	// <<, <, >, >>, |, ', ", (BONUS) &&, ||
	// ft_tokenizer(data);
	// ft_print_data(data);
	return (data);
}
