/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchbouki <rchbouki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 19:14:55 by thibnguy          #+#    #+#             */
/*   Updated: 2023/10/12 00:38:11 by rchbouki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

long long	ft_atoi(const char *str)
{
	int			i;
	long long	res;
	int			sign;

	i = 0;
	sign = 1;
	res = 0;
	if (ft_strcmp((char *)str, "-9223372036854775808") == 0)
	{
		res = -9223372036854775807;
		return (res - 1);
	}
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		if ((res > (LLONG_MAX - (str[i] - '0')) / 10))
			return (-1);
		res = res * 10 + (str[i] - '0');
		i++;
	}
	return (res * sign);
}
