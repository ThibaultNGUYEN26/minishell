/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thibnguy <thibnguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/17 18:41:02 by thibnguy          #+#    #+#             */
/*   Updated: 2023/06/17 18:42:03 by thibnguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*ft_strchr(char *s, int c)
{
	int	i;

	i = -1;
	while (s[++i] != (char)c)
		if (s[i] == '\0')
			return (NULL);
	return ((char *)s + i);
}
