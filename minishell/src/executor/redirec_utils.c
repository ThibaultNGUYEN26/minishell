/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirec_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchbouki <rchbouki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 14:22:02 by rchbouki          #+#    #+#             */
/*   Updated: 2023/09/25 18:43:29 by rchbouki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	ft_open_errors(char *filename)
{
	if (errno == ENOENT)
		printf("File '%s' does not exist.\n", filename);
	else if (errno == EACCES)
		printf("Permission denied for file '%s'.\n", filename);
	else
		printf("Error opening file '%s'. Error code: %d.\n", filename, errno);
	exit(errno);
}

void    ft_redirec_files(t_cmd *cmd, t_files *file)
{
    t_data  *redirec_head;

	file->input = -1;
	file->output = -1;
    if (cmd->redirections != NULL)
	{
		redirec_head = cmd->redirections;
		while (1)
		{
			if ((cmd->redirections)->token == 1)
			{
				if (file->input != -1)
					close(file->input);
				file->input = open((cmd->redirections)->next->content, O_RDONLY, 0777);
			}
			else if ((cmd->redirections)->token == 4)
				ft_here_doc((cmd->redirections)->next->content, file);
			else if ((cmd->redirections)->token == 2)
			{
				if (file->output != -1)
					close(file->output);
				file->output = open((cmd->redirections)->next->content, O_WRONLY, 0777);
			}
			else if ((cmd->redirections)->token == 3)
			{
				if (file->output != -1)
					close(file->output);
				file->output = open((cmd->redirections)->next->content, O_APPEND, 0777);
			}
			if (file->input == -1 || file->output == -1)
				ft_open_errors((cmd->redirections)->next->content);
			cmd->redirections = cmd->redirections->next;
			if (cmd->redirections == redirec_head)
				break ;
		}
	}
    else
    {
	    file->input = STDIN_FILENO;
	    file->output = STDOUT_FILENO;
    }
}

char	**ft_find_path(char **envp)
{
	char	**path;
	int		i;

	i = 0;
	path = NULL;
	while (envp[i] && ft_strncmp(envp[i], "PATH=", 5) != 0)
		i++;
	if (envp[i])
		path = ft_split(envp[i] + 5, ":");
	return (path);
}
