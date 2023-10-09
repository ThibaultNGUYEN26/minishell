/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirec_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thibnguy <thibnguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 14:22:02 by rchbouki          #+#    #+#             */
/*   Updated: 2023/10/09 19:09:22 by thibnguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	ft_open_errors(char *filename)
{
	char	*str;
	char	*temp;

	str = ft_strjoin2("minishell: ", filename);
	temp = ft_strdup(str);
	free(str);
	if (errno == ENOENT)
		str = ft_strjoin2(temp, ": No such file or directory\n");
	else if (errno == EACCES)
		str = ft_strjoin2(temp, ": Permission denied\n");
	else
		str = ft_strjoin2(temp, ": Error opening file\n");
	free(temp);
	ft_putstr_fd(str, 2);
	free(str);
}

static void	ft_output(t_cmd *cmd, t_files *file, int append)
{
	if (file->output != -2)
		close(file->output);
	if (append == 0)
		file->output = open((cmd->redirections)->next->content, O_CREAT | O_TRUNC | O_WRONLY, 0777);
	if (append == 1)
		file->output = open((cmd->redirections)->next->content, O_CREAT | O_APPEND | O_WRONLY, 0777);
	(cmd)->redirections = (cmd)->redirections->next;
	if (file->output == -1)
		ft_open_errors((cmd->redirections)->content);
}

static void	ft_input(t_cmd *cmd, t_files *file)
{
	if (file->input != -1)
	{	
		if (file->input != -2)
			close(file->input);
		file->input = open((cmd->redirections)->next->content, O_RDONLY, 0777);
		(cmd)->redirections = (cmd)->redirections->next;
		if (file->input == -1)
			ft_open_errors((cmd->redirections)->content);
	}
}

void    ft_redirec_files(t_cmd *cmd, t_files *file)
{
    t_data  *redirec_head;
	
    if (cmd->redirections != NULL)
	{
		redirec_head = cmd->redirections;
		while (1)
		{
			if ((cmd->redirections)->token == 1)
				ft_input(cmd, file);
			else if ((cmd->redirections)->token == 4)
			{
				if (file->input != -1)
				{
					if (file->input != -2)
						close(file->input);
					file->input = cmd->heredoc_file;
				}
			}
			else if ((cmd->redirections)->token == 2)
				ft_output(cmd, file, 0);
			else if ((cmd->redirections)->token == 3)
				ft_output(cmd, file, 1);
			if (file->output == -1)
			{
				cmd->redirections = redirec_head;
				break ;
			}
			cmd->redirections = (cmd->redirections)->next;
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
