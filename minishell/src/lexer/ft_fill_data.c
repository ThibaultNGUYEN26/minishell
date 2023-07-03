/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fill_data.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thibnguy <thibnguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 21:03:08 by thibnguy          #+#    #+#             */
/*   Updated: 2023/07/03 15:18:09 by thibnguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
  * Fill linked list with the user input.
  * @param input
  * @returns data
  */
t_data	*ft_fill_data(char *input)
{
	t_data	*data;
	char	**tab;
	int		i;

	tab = NULL;
	data = NULL;
	tab = ft_split(input, " ");
	i = -1;
	while (tab[++i])
		addlast_node(&data, ft_new_stack(tab[i]));
	free(tab);
	return (data);
}
