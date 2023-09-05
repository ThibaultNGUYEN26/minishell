/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thibnguy <thibnguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 17:52:08 by thibnguy          #+#    #+#             */
/*   Updated: 2023/09/05 19:53:38 by thibnguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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
static void	ft_catch_input(char *input, char **envp)
{
	t_data	*data;

	if (!input)
		ft_ctrl_d();
	else if (ft_strcmp(input, "exit") == 0)
		ft_exit(input);
	else if (ft_strcmp(input, "") == 0)
		return ;
	data = ft_lexer(input);
	ft_quotes_error(data);
	ft_quotes(data);
	ft_redirect_error(data);
	ft_dollar(data, envp);
	ft_print_data(data);
	ft_free_stack(data);
}

/**
  * Loop the user input and catch signals from it + history functionality.
  * @param envp
  * @returns void
  */
static void	ft_minishell_loop(char **envp)
{
	char	*input;
	
	input = NULL;
	// disable_echo();
	// signal(SIGINT, ft_ctrl_c);
	while (1)
	{
		input = readline(PROMPT);
		add_history(input);
		ft_catch_input(input, envp);
		free(input);
		input = NULL;
	}
}

int	main(int argc, char *argv[], char **envp)
{
	(void)argc;
	(void)argv;
	ft_welcome();
	ft_minishell_loop(envp);
	return (0);
}
