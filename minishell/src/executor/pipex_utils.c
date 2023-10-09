/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thibnguy <thibnguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 20:30:51 by thibnguy          #+#    #+#             */
/*   Updated: 2023/10/08 22:56:333 by thibnguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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

	ft_putstr_fd("heredoc> ", 2);
	line = get_next_line(STDIN_FILENO);
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

void	ft_assign_hd(t_cmd *cmd)
{
	t_cmd	*head;
	t_data	*redirec_head;

	head = cmd;
	while (1)
	{
		if (cmd->redirections)
		{
			redirec_head = cmd->redirections;
			while (1)
			{
				if ((cmd->redirections)->token == 4)
				{
					close(cmd->heredoc_file);
					ft_here_doc((cmd->redirections)->next->content, &(cmd->heredoc_file));
				}
				cmd->redirections = cmd->redirections->next;
				if (cmd->redirections == redirec_head)
					break ;
			}
		}
		cmd = cmd->next;
		if (cmd == head)
			break ;
	}
}
