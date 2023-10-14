/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   defines.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thibnguy <thibnguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/17 18:20:43 by thibnguy          #+#    #+#             */
/*   Updated: 2023/10/14 19:48:00 by thibnguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEFINES_H
# define DEFINES_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1
# endif

extern int	g_exit_code;
# define PATH_MAX 4096
# define RL_DEFAULT "\033[1;32m➜ \033[1;32mminishell\033[94m$▸\033[0m "
# define RL_ERROR "\033[31m➜ \033[1;32mminishell\033[94m$▸\033[0m "

#endif