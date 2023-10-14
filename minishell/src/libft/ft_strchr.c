/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thibnguy <thibnguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/17 18:41:02 by thibnguy          #+#    #+#             */
/*   Updated: 2023/10/14 12:58:19 by thibnguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
  * Checks if c is in s
  * @param char.*str
  * @param char.c
  * @returns int
  */
int	ft_strchr(char *s, char c)
{
	int	i;

	i = -1;
	while (s[++i] != c)
		if (s[i] == '\0')
			return (-1);
	return (i);
}
