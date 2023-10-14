/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirec_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thibnguy <thibnguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 14:22:02 by rchbouki          #+#    #+#             */
/*   Updated: 2023/10/14 19:06:21 by thibnguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
	* Handles output redirection for a command by opening a file for writing
	* @param t_cmd.*cmd
	* @param t_files.*file
	* @param int.append
	* @returns void
	*/
static void	ft_output(t_cmd *cmd, t_files *file, int append)
{
	if (file->output != STDOUT_FILENO)
		close(file->output);
	if (append == 0)
		file->output = open((cmd->redirections)->next->content, O_CREAT | \
			O_TRUNC | O_WRONLY, 0777);
	if (append == 1)
		file->output = open((cmd->redirections)->next->content, O_CREAT | \
			O_APPEND | O_WRONLY, 0777);
	(cmd)->redirections = (cmd)->redirections->next;
	if (file->output == -1)
		ft_exec_error((cmd->redirections)->content);
}

/**
	* Handles input redirection for a command by opening a file for reading
	* @param t_cmd.*cmd
	* @param t_files.*file
	* @returns void
	*/
static void	ft_input(t_cmd *cmd, t_files *file)
{
	if (file->input != -1)
	{
		if (file->input != STDIN_FILENO)
			close(file->input);
		file->input = open((cmd->redirections)->next->content, O_RDONLY, 0777);
		(cmd)->redirections = (cmd)->redirections->next;
		if (file->input == -1)
			ft_exec_error((cmd->redirections)->content);
	}
}

/**
	* Manages all redirections for a command by iterating through a list of
	* redirections
	* @param t_cmd.*cmd
	* @param t_files.*files
	* @param t_data.*redirec_head
	* @returns void
	*/
static void	ft_redirec_cmd(t_cmd *cmd, t_files *file, t_data *redirec_head)
{
	while (1)
	{
		if ((cmd->redirections)->token == 1)
			ft_input(cmd, file);
		else if ((cmd->redirections)->token == 4)
		{
			if (file->input != STDIN_FILENO)
				close(file->input);
			file->input = cmd->heredoc_file;
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

/**
	* Manages redirections for a command
	* @param t_cmd.*cmd
	* @param t_files.*file
	* @returns void
	*/
void	ft_redirec_files(t_cmd *cmd, t_files *file)
{
	t_data	*redirec_head;

	file->output = STDOUT_FILENO;
	if (cmd->redirections != NULL)
	{
		redirec_head = cmd->redirections;
		ft_redirec_cmd(cmd, file, redirec_head);
	}
}

/**
	* Searches for the 'PATH' environment variable in an array of environment
	* variables
	* @param char.**envp
	* @returns char **
	*/
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
