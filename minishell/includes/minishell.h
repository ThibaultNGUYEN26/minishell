/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thibnguy <thibnguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 17:52:35 by thibnguy          #+#    #+#             */
/*   Updated: 2023/10/15 16:30:15 by thibnguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <readline/readline.h>
# include <readline/history.h>
# include <sys/types.h>
# include <sys/errno.h>
# include <sys/wait.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <fcntl.h>
# include <errno.h>
# include <limits.h>
# include <termios.h>
# include <signal.h>
# include <stdbool.h>
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

typedef struct s_data
{
	char			*content;
	t_token			token;
	int				exit_code;
	struct s_data	*next;
	struct s_data	*prev;
}	t_data;

typedef struct s_bashvar
{
	char	**envp;
	char	*old_pwd;
	char	*pwd;
	int		error_num;
}	t_bashvar;

typedef struct s_files
{
	int	input;
	int	output;
	int	saved_input;
	int	saved_output;
	int	saved_error;
	int	argc;
	int	*pid;
}	t_files;

typedef struct s_cmd
{
	char			**command;
	int				(*builtin)(struct s_cmd *, struct s_bashvar **);
	t_data			*redirections;
	int				heredoc_file;
	int				error;
	struct s_cmd	*next;
	struct s_cmd	*prev;
}	t_cmd;

typedef struct s_var
{
	int		i;
	int		j;
	int		k;
	int		test;
	int		ancien;
	char	*temp;
}	t_var;

/* ----- BASHVAR ----- */
/* ft_bash */
void		ft_bash(t_bashvar **bash, char **envp);
void		ft_free_bash(t_bashvar **bash);

/* ----- BUILTINS ----- */
/* ft_builtins */
void		ft_builtin(t_cmd *cmd, t_bashvar **bash);
int			ft_cd(t_cmd *cmd, t_bashvar **bash);
int			ft_echo(t_cmd *cmd, t_bashvar **bash);
int			ft_env(t_cmd *cmd, t_bashvar **bash);
int			ft_exit(t_cmd *cmd, t_bashvar **bash);
void		ft_replace(char **export_value, t_bashvar ***bash);
void		ft_add(char *export_value, t_bashvar ***bash);
int			ft_export(t_cmd *cmd, t_bashvar **bash);
int			ft_pwd(t_cmd *cmd, t_bashvar **bash);
int			ft_thibnguy(t_cmd *cmd, t_bashvar **bash);
int			ft_unset(t_cmd *cmd, t_bashvar **bash);

/* ------ EXECUTOR ----- */
/* ft_exec_error.c */
int			ft_exec_error(char *cmd);
/* ft_heredoc.c */
void		ft_here_doc(char *delimiter, int *input);
/* pipex_utils.c */
int			create_process(int *pfd, int pid);
void		ft_assign_hd(t_cmd *cmd);
/* pipex.c */
void		ft_handle_cmd(t_cmd *cmd, t_bashvar **bash);
/* ft_redirec_files.c */
void		ft_redirec_files(t_cmd *cmd, t_files *file);
char		**ft_find_path(char **envp);
/* ft_exec_utils.c */
void		ft_execve_utils(char **path, t_cmd *cmd);
int			ft_builtin_parent(t_files *file, t_cmd *cmd, t_bashvar **bash);
void		ft_parent_exec(t_files *file, int n, int pid, t_cmd *cmd);

/* ----- GET_NEXT_LINE ----- */
/* get_next_line_utils */
char		*ft_strchr2(char *s, int c);
char		*ft_strjoin2(char *s1, char *s2);
/* get_next_line */
char		*get_next_line(const int fd);

/* ----- LEXER ----- */
/* ft_dollar_utils */
int			ft_check_dollar(char c, char **res, int i);
int			ft_norminette(int *i, int *j, t_data *data, char **res);
void		ft_dollar_init(t_data *data, int *i, int *j, char **res);
int			ft_question_mark(char *data, char **res, int i, int j);
/* ft_dollar */
void		ft_dollar(t_data *data, char **envp);
/* ft_lexer_errors */
int			ft_quotes_input(char *input);
int			ft_quotes_error(t_data *data);
int			ft_redirect_error(t_data *data);
/* ft_lexer_file_errors */
int			ft_check_filecharacters(t_data *data);
/* ft_lexer */
t_data		*ft_lexer(char *input);
/* ft_quotes.c */
void		ft_quotes(t_data *data);

/* ----- LIBFT ----- */
long long	ft_atoi(const char *str);
int			ft_isalnum(int c);
int			ft_isnumeric(char *str);
char		*ft_itoa(int n);
void		ft_putstr_fd(char *s, int fd);
void		ft_putchar_fd(char c, int fd);
int			ft_count_words(char *str, char *charset);
char		**ft_split(char *str, char *charset);
int			ft_strchr(char *s, char c);
int			ft_strcmp(char *s1, char *s2);
char		*ft_strdup(char *s);
char		*ft_strjoin(char *s1, char *s2);
int			ft_strlen(char *s);
int			ft_strncmp(char *s1, char *s2, unsigned int n);
char		*ft_substr(char *s, int start, int len);

/* ----- PARSER ----- */
/* ft_echo_utils */
int			ft_echo_help(t_data **data, t_var *var, t_cmd *cmd, char **split);
void		ft_free_split(char **s, int j);
void		ft_not_echo(t_cmd *cmd, int *i, char **split, int *j);
/* ft_parser_echo */
int			ft_white_space(char content);
int			ft_echo_error(t_data **data, t_cmd *cmd, char **split, \
t_data *head);
/* ft_parser_init */
void		ft_cmd_init(t_cmd **cmd, t_cmd **head_cmd);
void		ft_data_init(t_data **data, t_data **head_data, t_data **head_pipe);
void		ft_create_cmd(t_cmd **cmd, t_cmd **head_cmd);
void		ft_update_ptr(t_data **data, t_data **after_pipe, \
t_data **head_pipe);
int			ft_check_element(t_data **data, t_cmd *cmd);
/* ft_parser_redirec */
int			ft_invalid_redirec(t_data **data, t_data *head_data);
int			ft_redirec(t_data **head, t_data **data, t_cmd *cmd, t_data **pipe);
/* ft_parser_utils */
void		ft_command_parser(t_cmd *cmd, t_data **data, t_data *after_pipe);
/* ft_parser */
t_cmd		*ft_parser(t_data **data);

/* ------ SIGNALS ----- */
/* ft_signals */
bool		get_hd_bool(bool set, bool value);
void		sigint_handler(int sig);
void		ft_heredoc_handler(int sig);
void		ft_signals(void);

/* ----- UTILS ----- */
/* ft_cmds_utils */
t_cmd		*ft_new_cmd(void);
void		addlast_cmd(t_cmd **stack, t_cmd *new_cmd);
void		ft_print_cmd(t_cmd *cmd);
void		ft_free_cmd(t_cmd *cmd);
/* ft_stack_utils */
t_data		*ft_new_stack(char *content, char *token);
void		addlast_node(t_data **stack, t_data *new_data);
void		ft_delete_element(t_data **data);
t_data		*ft_data_copy(t_data *data);
void		ft_free_stack(t_data *data);
void		ft_print_data(t_data *data);

#endif