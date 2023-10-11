/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thibnguy <thibnguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 17:52:08 by thibnguy          #+#    #+#             */
/*   Updated: 2023/10/11 23:18:55 by thibnguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	exit_code = 0;

/**
  * Print welcome text at program's launch.
  * @param void 
  * @returns 0 file open success | 1 file open failed
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
  * @param input
  * @param envp
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
	/* if (ft_quotes_error(data))
	{
		ft_free_stack(data);
		return ;
	}*/
	if (ft_redirect_error(data))
	{
		ft_free_stack(data);
		return ;
	}
	ft_dollar(data, (*bash)->envp);
	printf("STRUCTURE DU LEXER :\n");
	ft_print_data(data);
	cmd = ft_parser(&data);
	if (cmd->error == 1)
	{
		ft_free_stack(data);
		ft_free_cmd(cmd);
		return ;
	}
	// if data->exit_code == 1 ou == 2 à ce niveau du code it means invalid file
	//after redirection donc as if CTRL-C donc il ne faut PAS faire l'executable
	if (data != NULL)
		ft_free_stack(data);
	ft_builtin(cmd, bash);
	printf("STRUCTURE DU PARSER :\n");
	ft_print_cmd(cmd);
	printf("EXECUTION INCOMING\n");
	ft_handle_cmd(cmd, bash);
	ft_free_cmd(cmd);
}

/**
  * Loop the user input and catch signals from it + history functionality.
  * @param envp
  * @returns void
  */
static void	ft_minishell_loop(t_bashvar **bash)
{
	char	*input;

	(void)bash;
	ft_signals();
	while (1)
	{
		input = NULL;
		if (exit_code == 0)
			input = readline("\033[1;32m➜ \033[1;32mminishell\033[94m$▸\033[0m ");
		else
			input = readline("\033[31m➜ \033[1;32mminishell\033[94m$▸\033[0m ");
		// input = readline("minishell$> ");
		if (!input)
		{
			exit_code = 0;
			printf("exit\n");
			break ;
		}
		add_history(input);
		ft_catch_input(input, bash);
		free(input);
	}
}

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
