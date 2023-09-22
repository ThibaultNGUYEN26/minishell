/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchbouki <rchbouki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 20:30:51 by thibnguy          #+#    #+#             */
/*   Updated: 2023/09/21 14:14:28 by rchbouki         ###   ########.fr       */
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
	cmd = ft_strjoin(envp, "/");
	return (cmd);
}

int	create_process(int n, int *pfd, int pid)
{
	if (n == 0)
		exit(EXIT_SUCCESS);
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

	str = ft_strdup(line, 0);
	str[ft_strlen(str) - 1] = '\0';
	return (str);
}

static void	ft_child_heredoc(int *pfd, char **argv)
{
	char	*line;
	char	*str;

	ft_printf("pipe heredoc> ");
	line = get_next_line(STDIN_FILENO);
	str = ft_line_heredoc(line);
	while (ft_strcmp(str, argv[2]) != 0)
	{
		ft_printf("pipe heredoc> ");
		write(pfd[1], line, ft_strlen(line));
		line = get_next_line(STDIN_FILENO);
		str = ft_line_heredoc(line);
	}
	free(str);
	free(line);
	close(pfd[1]);
}

void	ft_here_doc(char **argv, t_files *file, int *argc)
{
	int		status;
	int		pfd[2];
	int		pid;

	pid = create_process(1, pfd, 0);
	if (pid == 0)
	{
		close(pfd[0]);
		ft_child_heredoc(pfd, argv);
		exit(0);
	}
	else
	{
		close(pfd[1]);
		file->input = dup(pfd[0]);
		close(pfd[0]);
		waitpid(pid, &status, 0);
	}
	*argc -= 1;
}
