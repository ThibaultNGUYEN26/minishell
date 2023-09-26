/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirec_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchbouki <rchbouki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 14:22:02 by rchbouki          #+#    #+#             */
/*   Updated: 2023/09/26 21:29:33 by rchbouki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	ft_open_errors(char *filename)
{
	char	*str;
	char	*temp;
	
	temp = NULL;
	if (errno == ENOENT)
	{
		str = ft_strjoin2("File \'", filename);
		temp = str;
		free(str);
		str = ft_strjoin2(temp, "\' does not exist.\n");
		ft_putstr_fd(str, 2);
		free(str);
		free(temp);
	}
	else if (errno == EACCES)
		printf("Permission denied for file '%s'.\n", filename);
	else
	{
		
		printf("Error opening file '%s'. Error code: %d.\n", filename, errno);
	}
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
				file->output = open((cmd->redirections)->next->content, O_CREAT | O_TRUNC | O_WRONLY, 0777);
				printf("OUTPUUT %d\n", file->output);
				printf("INPUT %d\n", file->input);
			}
			else if ((cmd->redirections)->token == 3)
			{
				if (file->output != -1)
					close(file->output);
				file->output = open((cmd->redirections)->next->content, O_CREAT | O_TRUNC | O_APPEND, 0777);
			}
			if (file->input == -1 || file->output == -1)
				ft_open_errors((cmd->redirections)->next->content);
			cmd->redirections = cmd->redirections->next;
			if (cmd->redirections == redirec_head)
				break ;
		}
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
