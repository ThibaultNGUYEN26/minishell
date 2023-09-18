/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thibnguy <thibnguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 17:52:35 by thibnguy          #+#    #+#             */
/*   Updated: 2023/09/18 23:09:52 by thibnguy         ###   ########.fr       */
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
	t_token			token;
	int				exit_code;
	struct s_data	*next;
	struct s_data	*prev;
	int				ctrl_c_status;
}	t_data;

typedef struct s_bashvar
{
	char					**envp;
	char					*pwd;
	char					*old_pwd;
}	t_bashvar;

typedef struct s_cmd
{
	char			**command;
	int				(*builtin)(struct s_cmd *, struct s_bashvar **);
	t_data			*redirections;
	struct s_cmd	*next;
	struct s_cmd	*prev;
}	t_cmd;

/* ----- BASHVAR ----- */
/* ft_bash */
void	ft_bash(t_bashvar **bash, char **envp);
void	ft_free_bash(t_bashvar **bash);

/* ----- BUILTINS ----- */
/* ft_builtins */
void	ft_builtin(t_cmd *cmd, t_bashvar **bash);
int		ft_cd(t_cmd *cmd, t_bashvar **bash);
int		ft_echo(t_cmd *cmd, t_bashvar **bash);
int		ft_env(t_cmd *cmd, t_bashvar **bash);
int		ft_exit(t_cmd *cmd, t_bashvar **bash);
int		ft_export(t_cmd *cmd, t_bashvar **bash);
int		ft_pwd(t_cmd *cmd, t_bashvar **bash);
int		ft_unset(t_cmd *cmd, t_bashvar **bash);

/* ----- GET_NEXT_LINE ----- */
char	*get_next_line(const int fd);
/* get_next_line_utils */
char	*ft_strchr2(char *s, int c);
char	*ft_strjoin2(char *s1, char *s2);

/* ----- LEXER ----- */
/* ft_dollar */
void	ft_dollar(t_data *data, char **envp);
/* ft_lexer_errors */
void	ft_quotes_error(t_data *data);
void	ft_redirect_error(t_data *data);
/* ft_lexer */
t_data	*ft_lexer(char *input);
void	ft_quotes(t_data *data);

/* ----- LEXER ----- */
/* ft_parser */
t_cmd	*ft_parser(t_data **my_data);

/* ----- LIBFT ----- */
void	ft_putstr_fd(char *s, int fd);
int		ft_count_words(char *str, char *charset);
char	**ft_split(char *str, char *charset);
int		ft_strchr(char *s, char c);
int		ft_strcmp(char *s1, char *s2);
char	*ft_strdup(char *s);
char	*ft_strjoin(char *s1, char *s2);
int		ft_strlen(char *s);
int		ft_strncmp(char *s1, char *s2, unsigned int n);
char	*ft_substr(char *s, int start, int len);

/* ------ SIGNALS ----- */
void	ft_ctrl_d(void);

/* ----- UTILS ----- */
/* ft_cmds_utils */
t_cmd	*ft_new_cmd(void);
void	addlast_cmd(t_cmd **stack, t_cmd *new_cmd);
void	ft_print_cmd(t_cmd *cmd);
void	ft_free_cmd(t_cmd *cmd);
/* ft_stack_utils */
t_data	*ft_new_stack(char *content, char *token);
void	addlast_node(t_data **stack, t_data *new_data);
void	ft_delete_element(t_data **data);
t_data	*ft_data_copy(t_data *data);
void	ft_free_stack(t_data *data);
void	ft_print_data(t_data *data);

#endif