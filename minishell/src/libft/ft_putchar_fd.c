/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putchar_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thibnguy <thibnguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/08 11:34:13 by rchbouki          #+#    #+#             */
/*   Updated: 2023/10/14 12:50:29 by thibnguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
  * write a single character to a given file descriptor
  * @param char.c
  * @param int.fd
  * @returns void
  */
void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}
