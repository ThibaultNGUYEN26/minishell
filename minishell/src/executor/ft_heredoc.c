/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_heredoc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thibnguy <thibnguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 21:09:37 by thibnguy          #+#    #+#             */
/*   Updated: 2023/10/12 23:20:33 by thibnguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	*ft_line_heredoc(char *line)
{
	char	*str;

	str = ft_strdup(line);
	str[ft_strlen(str) - 1] = '\0';
	return (str);
}

static int	ft_signal_heredoc(char *line, char *str, char *delimiter)
{
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

static void	ft_child_heredoc(int *pfd, char *delimiter)
{
	char	*line;
	char	*str;

	signal(SIGINT, &ft_heredoc_handler);
	ft_putstr_fd("heredoc> ", 2);
	line = get_next_line(STDIN_FILENO);
	str = NULL;
	if (ft_signal_heredoc(line, str, delimiter))
		return ;
	str = ft_line_heredoc(line);
	while (ft_strcmp(str, delimiter) != 0)
	{
		ft_putstr_fd("heredoc> ", 2);
		write(pfd[1], line, ft_strlen(line));
		free(line);
		line = get_next_line(STDIN_FILENO);
		free(str);
		str = ft_line_heredoc(line);
	}
	free(str);
	free(line);
	close(pfd[1]);
}

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
		exit(EXIT_SUCCESS);
	}
	else
	{
		close(pfd[1]);
		*input = dup(pfd[0]);
		close(pfd[0]);
		waitpid(pid, &status, 0);
	}
}
