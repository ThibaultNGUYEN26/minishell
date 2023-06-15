/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nblen.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thibnguy <thibnguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 18:09:15 by thibnguy          #+#    #+#             */
/*   Updated: 2023/06/15 18:09:31 by thibnguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_nblen(long n, char *base)
{
	int	len;

	len = 0;
	while (n)
	{
		n /= ft_strlen(base);
		len++;
	}
	return (len);
}
