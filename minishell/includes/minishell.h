/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thibnguy <thibnguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 17:52:35 by thibnguy          #+#    #+#             */
/*   Updated: 2023/06/15 18:15:19 by thibnguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdarg.h>

# define BLACK	"\033[1;30m"
# define RED	"\033[1;31m"
# define GREEN	"\033[1;32m"
# define CYAN	"\033[1;35m"
# define BLUE	"\033[1;36m"
# define WHITE	"\033[1;37m"
# define EOC	"\033[0;0m"

/* libft */
int	ft_putchar(char c);
int	ft_putnbr_base(long long nb, char *base);
int	ft_putstr(char *s);
int	ft_strlen(char *s);

/* ft_printf */
int	ft_nblen(long n, char *base);
int	ft_printf(const char *s, ...);

#endif