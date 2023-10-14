/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_heredoc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thibnguy <thibnguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 21:09:37 by thibnguy          #+#    #+#             */
/*   Updated: 2023/10/14 23:28:23 by thibnguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
	* Ctrl+d in heredoc
	* @param char.*line
	* @param char.*delimiter
	* @returns int
	*/
static int	ft_signal_heredoc(char *line, char *delimiter)
{
	char	*str;

	str = NULL;
	if (!line)
	{
		str = ft_strjoin(ft_strdup("minishell: warning: here-document delimited \
by end-of-file (wanted `"), \
			ft_substr(delimiter, 0, ft_strlen(delimiter)));
		str = ft_strjoin(str, ft_strdup("')\n"));
		ft_putstr_fd(str, 2);
		free(str);
		return (1);
	}
	return (0);
}

/**
	* Execute heredoc
	* @param int.*pfd
	* @param char.*delimiter
	* @returns void
	*/
static void	ft_child_heredoc(int *pfd, char *delimiter)
{
	char	*line;

	line = NULL;
	signal(SIGINT, &ft_heredoc_handler);
	while (1)
	{
		line = readline("\033[94mheredoc▸\033[0m ");
		if (ft_signal_heredoc(line, delimiter) || !ft_strcmp(line, delimiter))
			return (free(line));
		write(pfd[1], line, ft_strlen(line));
		write(pfd[1], "\n", 1);
		free(line);
	}
	close(pfd[1]);
}

/**
	* Manages heredoc
	* @param char.*delimiter
	* @param int.*input
	* @returns void
	*/
void	ft_here_doc(char *delimiter, int *input)
{
	int		status;
	int		pfd[2];
	int		pid;

	pid = create_process(pfd, 0);
	if (pid == 0)
	{
		close(pfd[0]);
		ft_child_heredoc(pfd, delimiter);
		exit(g_exit_code);
	}
	else
	{
		close(pfd[1]);
		*input = dup(pfd[0]);
		close(pfd[0]);
		waitpid(pid, &status, 0);
		if (WIFEXITED(status))
			g_exit_code = WEXITSTATUS(status);
	}
}
