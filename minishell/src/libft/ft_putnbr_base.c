/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_base.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thibnguy <thibnguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 18:04:28 by thibnguy          #+#    #+#             */
/*   Updated: 2023/06/15 18:05:12 by thibnguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_putnbr_base(long long nb, char *base)
{
	int			sign;

	sign = 0;
	if (nb < 0)
	{
		nb = -nb;
		write(1, "-", 1);
		sign = 1;
	}
	if (nb >= (long long)ft_strlen(base))
	{
		ft_putnbr_base(nb / ft_strlen(base), base);
		ft_putnbr_base(nb % ft_strlen(base), base);
	}
	else
		ft_putchar(base[nb]);
	if (nb == 0)
		return (sign + ft_nblen(nb, base) + 1);
	return (sign + ft_nblen(nb, base));
}
