/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thibnguy <thibnguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 17:52:08 by thibnguy          #+#    #+#             */
/*   Updated: 2023/09/18 18:23:40 by thibnguy         ###   ########.fr       */
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
	t_cmd	*cmd;

	if (!input)
		ft_ctrl_d();
	else if (ft_strcmp(input, "") == 0)
		return ;
	data = ft_lexer(input);
	ft_quotes_error(data);
	ft_quotes(data);
	ft_redirect_error(data);
	ft_dollar(data, envp);
	printf("STRUCTURE DU LEXER :\n");
	ft_print_data(data);
	cmd = ft_parser(&data);
	// if data->exit_code == 3 ou == 2 à ce niveau du code it means invalid file
	//after redirection donc as if CTRL-C donc il ne faut PAS faire l'executable
	printf("STRUCTURE DU LEXER APRES LE PARSING : ");
	ft_print_data(data);
	printf("STRUCTURE DU PARSER :\n");
	ft_print_cmd(cmd);
	if (data != NULL)
		ft_free_stack(data);
}

/**
  * Loop the user input and catch signals from it + history functionality.
  * @param envp
  * @returns void
  */
static void	ft_minishell_loop(t_bashvar *bash)
{
	char	*input;

	input = NULL;
	while (1)
	{
		input = readline(PROMPT);
		add_history(input);
		ft_catch_input(input, bash->envp);
		free(input);
		input = NULL;
	}
}

int	main(int argc, char *argv[], char **envp)
{
	t_bashvar	*bash;

	(void)argc;
	(void)argv;
	bash = ft_bash(bash, envp);
	ft_welcome();
	ft_minishell_loop(bash);
	return (0);
}
