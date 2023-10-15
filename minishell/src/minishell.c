/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thibnguy <thibnguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 17:52:08 by thibnguy          #+#    #+#             */
/*   Updated: 2023/10/15 16:37:57 by thibnguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	g_exit_code = 0;

/**
  * Print welcome text at program's launch.
  * @param void 
  * @returns int
  */
int	ft_welcome(void)
{
	int		fd;
	char	*line;

	line = NULL;
	fd = open("src/welcome.txt", O_RDONLY);
	if (fd == -1)
	{
		printf("Failed to open the file.\n");
		return (1);
	}
	line = get_next_line(fd);
	while (line)
	{
		printf(MAGENTA"%s"EOC, line);
		free(line);
		line = get_next_line(fd);
	}
	printf("\n\n");
	return (close(fd), 0);
}

/**
  * Input catcher and run lexer
  * @param char.*input
  * @param t_bashvar.**bash
  * @returns void
  */
static void	ft_catch_input(char *input, t_bashvar **bash)
{
	t_data	*data;
	t_cmd	*cmd;

	if (ft_strcmp(input, "") == 0)
		return ;
	if (ft_quotes_input(input) == 1)
		return ;
	data = ft_lexer(input);
	ft_quotes(data);
	if (ft_redirect_error(data))
		return (ft_free_stack(data));
	ft_dollar(data, (*bash)->envp);
	cmd = ft_parser(&data);
	if (cmd->error == 1)
	{
		ft_free_stack(data);
		return (ft_free_cmd(cmd));
	}
	if (data != NULL)
		ft_free_stack(data);
	ft_builtin(cmd, bash);
	ft_handle_cmd(cmd, bash);
	ft_free_cmd(cmd);
}

/**
  * Loop the user input and catch signals from it + history functionality.
  * @param t_bashvar.**bash
  * @returns void
  */
static void	ft_minishell_loop(t_bashvar **bash)
{
	char	*input;

	input = NULL;
	ft_signals();
	while (1)
	{
		get_hd_bool(true, false);
		if (g_exit_code == 0)
			input = readline(RL_DEFAULT);
		else
			input = readline(RL_ERROR);
		get_hd_bool(true, true);
		if (!input)
		{
			g_exit_code = 0;
			printf("exit\n");
			return ;
		}
		add_history(input);
		ft_catch_input(input, bash);
		free(input);
	}
}

/**
  * Entry point of the program that initializes the shell environment, displays
  * a welcome message, enters a shell loop, and cleans up allocated resources
  * @param int.argc
  * @param char.*argv[]
  * @param char.**envp
  * @returns int
  */
int	main(int argc, char *argv[], char **envp)
{
	t_bashvar	*bash;

	(void)argc;
	(void)argv;
	bash = malloc(sizeof(t_bashvar) * 1);
	if (!bash)
		return (1);
	ft_bash(&bash, envp);
	ft_welcome();
	ft_minishell_loop(&bash);
	ft_free_bash(&bash);
	return (0);
}
