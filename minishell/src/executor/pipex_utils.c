/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thibnguy <thibnguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 19:07:01 by thibnguy          #+#    #+#             */
/*   Updated: 2023/10/12 21:18:22 by thibnguy         ###   ########.fr       */
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

static void	ft_if_heredoc(t_cmd *cmd, t_data *redirec_head)
{
	while (1)
	{
		if ((cmd->redirections)->token == 4)
		{
			close(cmd->heredoc_file);
			ft_here_doc((cmd->redirections)->next->content, \
				&(cmd->heredoc_file));
		}
		cmd->redirections = cmd->redirections->next;
		if (cmd->redirections == redirec_head)
			break ;
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
			ft_if_heredoc(cmd, redirec_head);
		}
		cmd = cmd->next;
		if (cmd == head)
			break ;
	}
}
