/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thibnguy <thibnguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 17:52:35 by thibnguy          #+#    #+#             */
/*   Updated: 2023/06/27 19:19:40 by thibnguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>
# include <string.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <termios.h>
# include <termcap.h>
# include "colors.h"
# include "defines.h"

typedef struct s_input
{
	char	*content;
	int		ctrl_c_status;
}	t_input;

/* get_next_line */
char	*get_next_line(const int fd);

/* libft */
char	*ft_strchr(char *s, int c);
int		ft_strcmp(char *s1, char *s2);
char	*ft_strdup(char *s);
char	*ft_strjoin(char *s1, char *s2);
int		ft_strlen(char *s);
char	*ft_substr(char *s, int start, int len);

/* signals */
void	ft_exit(t_input *input);
void	disable_echo(void);
void	ft_ctrl_d(void);
void	ft_ctrl_c(int sig);

/* utils */
int		ft_welcome(void);
void	ft_minishell_loop(void);

#endif