/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchbouki <rchbouki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 20:30:51 by thibnguy          #+#    #+#             */
/*   Updated: 2023/10/05 20:12:13 by rchbouki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*ft_command(char *envp, int len_cmd)
{
	char	*cmd;
	int		len;

	len = ft_strlen(envp);
	cmd = malloc((len + len_cmd) * sizeof(char));
	if (!cmd)
		return (NULL);
	cmd = ft_strjoin2(envp, "/");
	return (cmd);
}

int	create_process(int *pfd, int pid)
{
	if (pipe(pfd) < 0)
		exit(EXIT_FAILURE);
	pid = fork();
	if (pid < 0)
		exit(EXIT_FAILURE);
	return (pid);
}

static char	*ft_line_heredoc(char *line)
{
	char	*str;

	str = ft_strdup(line);
	str[ft_strlen(str) - 1] = '\0';
	return (str);
}

static void	ft_child_heredoc(int *pfd, char *delimiter)
{
	char	*line;
	char	*str;

	ft_putstr_fd("pipe heredoc> ", 2);
	line = get_next_line(STDIN_FILENO);
	str = ft_line_heredoc(line);
	while (ft_strcmp(str, delimiter) != 0)
	{
		ft_putstr_fd("pipe heredoc> ", 2);
		write(pfd[1], line, ft_strlen(line));
		line = get_next_line(STDIN_FILENO);
		str = ft_line_heredoc(line);
	}
	free(str);
	free(line);
	close(pfd[1]);
}

void	ft_here_doc(char *delimiter, t_files *file)
{
	int		status;
	int		pfd[2];
	int		pid;

	pid = create_process(pfd, 0);
	if (pid == 0)
	{
		close(pfd[0]);
		ft_putstr_fd("In the child of the Heredoc\n", 2);
		ft_child_heredoc(pfd, delimiter);
		exit(EXIT_SUCCESS);
	}
	else
	{
		close(pfd[1]);
		if (file->input != -1)
			close(file->input);
		file->input = dup(pfd[0]);
		close(pfd[0]);
		waitpid(pid, &status, 0);
	}
}
