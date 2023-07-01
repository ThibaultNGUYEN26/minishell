/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thibnguy <thibnguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 17:52:35 by thibnguy          #+#    #+#             */
/*   Updated: 2023/07/01 10:06:54 by thibnguy         ###   ########.fr       */
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
# include "colors.h"
# include "defines.h"

typedef struct s_data
{
	char			*content;
	struct s_data	*next;
	struct s_data	*prev;
	int				ctrl_c_status;
}	t_data;

/* get_next_line */
char	*get_next_line(const int fd);

/* lexer */
t_data	*ft_lexer(char *input);
t_data	*ft_fill_data(char *input);

/* libft */
char	**ft_split(char *str, char *charset);
char	*ft_strchr(char *s, int c);
int		ft_strcmp(char *s1, char *s2);
char	*ft_strdup(char *s);
char	*ft_strjoin(char *s1, char *s2);
int		ft_strlen(char *s);
char	*ft_substr(char *s, int start, int len);

/* signals */
void	ft_exit(char *input);
// void	disable_echo(void);
void	ft_ctrl_d(void);
// void	ft_ctrl_c(int sig);

/* utils */
t_data	*ft_new_stack(char *content);
void	addlast_node(t_data **stack, t_data *new_data);
void	ft_free_stack(t_data *data);
void	ft_print_data(t_data *data);
int		ft_welcome(void);
void	ft_minishell_loop(void);

#endif