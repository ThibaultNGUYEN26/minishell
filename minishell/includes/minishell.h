/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thibnguy <thibnguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 17:52:35 by thibnguy          #+#    #+#             */
/*   Updated: 2023/09/05 19:45:34 by thibnguy         ###   ########.fr       */
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

typedef enum s_token
{
	PIPE,
	INPUT,
	OUTPUT,
	APPEND,
	HEREDOC,
	NONE,
}	t_token;

/* for the moment exit_code 2 means unclosed quotes */
typedef struct s_data
{
	char			*content;
	char			*builtins;
	t_token			token;
	int				exit_code;
	struct s_data	*next;
	struct s_data	*prev;
	int				ctrl_c_status;
}	t_data;

/* typedef struct s_cmds
{
	char                    **str;
	int                     (*builtin)(t_tools *, struct s_cmds *);
	int                     num_redirections;
	char                    *hd_file_name;
	t_data                 *redirections;
	struct s_cmds	*next;
	struct s_cmds	*prev;
}	t_cmds; */

/* ----- GET_NEXT_LINE ----- */
char	*get_next_line(const int fd);
/* get_next_line_utils */
char	*ft_strchr2(char *s, int c);
char	*ft_strjoin2(char *s1, char *s2);

/* ----- LEXER_PARSER ----- */
/* ft_builtins */
void	ft_builtins(t_data *data, char *input);
/* ft_fill_data */
t_data	*ft_fill_data(char *input, char **envp);
/* ft_lexer */
t_data	*ft_lexer(char *input);
void	ft_quotes(t_data *data);
void	ft_dollar(t_data *data, char **envp);
/* ft_lexer_errors */
void	ft_quotes_error(t_data *data);
void    ft_redirect_error(t_data *data);

/* ----- LIBFT ----- */
char	**ft_split(char *str, char *charset);
int		ft_strchr(char *s, char c);
int		ft_strcmp(char *s1, char *s2);
char	*ft_strdup(char *s);
char	*ft_strjoin(char *s1, char *s2);
int		ft_strlen(char *s);
int		ft_strncmp(char *s1, char *s2, unsigned int n);
char	*ft_substr(char *s, int start, int len);

/* ------ SIGNALS ----- */
void	ft_exit(char *input);
// void	disable_echo(void);
void	ft_ctrl_d(void);
// void	ft_ctrl_c(int sig);

/* ----- UTILS ----- */
/* ft_stack_utils */
t_data	*ft_new_stack(char *content, char *token);
void	addlast_node(t_data **stack, t_data *new_data);
void	ft_free_stack(t_data *data);
void	ft_print_data(t_data *data);

/* ft_welcome */
int		ft_welcome(void);

/* minishell_loop */
void	ft_minishell_loop(char **envp);

#endif