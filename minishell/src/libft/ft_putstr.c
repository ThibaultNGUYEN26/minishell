/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thibnguy <thibnguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 18:03:47 by thibnguy          #+#    #+#             */
/*   Updated: 2023/06/15 18:03:58 by thibnguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_putstr(char *s)
{
	if (s)
		write(1, s, ft_strlen(s));
	else
		return (write(1, "(null)", 6), 6);
	return (ft_strlen(s));
}
