/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thibnguy <thibnguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 20:30:54 by thibnguy          #+#    #+#             */
/*   Updated: 2023/10/15 13:23:35 by thibnguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
  * Handles the setup of file descriptors for input and output redirection in
  * the child process
  * @param int.n
  * @param int.*pfd
  * @param t_files.*file
  * @returns void
  */
static void	ft_child(int n, int *pfd, t_files *file)
{
	close(pfd[0]);
	if (file->input != STDIN_FILENO)
	{
		dup2(file->input, STDIN_FILENO);
		close(file->input);
	}
	if (file->output != STDOUT_FILENO)
	{
		dup2(file->output, STDOUT_FILENO);
		close(file->output);
	}
	else if (n != 1)
	{
		dup2(pfd[1], STDOUT_FILENO);
		close(pfd[1]);
	}
	if (file->input == -1)
		exit(g_exit_code);
}

/**
  * Executes command, either as a builtin command or an external executable
  * @param t_files.*file
  * @param t_cmd.*cmd
  * @param t_bashvar.**bash
  * @returns void
  */
static void	ft_exec_cmd(t_files *file, t_cmd *cmd, t_bashvar **bash)
{
	char	**path;

	path = NULL;
	if (cmd->command == NULL)
		exit(EXIT_SUCCESS);
	if (cmd->builtin != NULL && file->argc == 1)
		exit(EXIT_SUCCESS);
	if (cmd->builtin != NULL && file->argc != 1)
		exit((cmd->builtin)(cmd, bash));
	if (access(cmd->command[0], X_OK) == 0)
		if (execve(cmd->command[0], cmd->command, NULL) == -1)
			exit(ft_exec_error("execve"));
	if ((*bash)->envp)
		path = ft_find_path((*bash)->envp);
	ft_execve_utils(path, cmd);
}

/**
  * Manages the execution of a pipeline of commands, creating process for each
  * command, handling input and output redirection, and executing the commands
  * @param int.n
  * @param t_cmd.*cmd
  * @param t_bashvar.**bash
  * @param t_files.*file
  * @returns void
  */
static void	ft_pipeline(int n, t_cmd *cmd, t_bashvar **bash, t_files *file)
{
	int		pfd[2];
	int		pid;

	ft_redirec_files(cmd, file);
	pid = create_process(pfd, 0);
	if (pid == 0)
	{
		ft_child(n, pfd, file);
		ft_exec_cmd(file, cmd, bash);
	}
	else
	{
		close(pfd[1]);
		if (ft_builtin_parent(file, cmd, bash))
			return ;
		ft_parent_exec(file, n, pid, cmd);
		if (file->input == -1)
			file->input = dup(pfd[0]);
		else
			dup2(pfd[0], file->input);
		close(pfd[0]);
		n--;
		if (n != 0)
			ft_pipeline(n, cmd->next, bash, file);
	}
}

/**
  * Initializes file descriptors and manages the execution of a series of
  * commands, setting up input and output redirection, executing the commands in
  * a pipeline, and restoring the standard input and output
  * @param t_files.*file
  * @param int.count
  * @param t_cmd.*cmd
  * @param t_bashvar.**bash
  * @returns int
  */
static int	ft_init_file(t_files *file, int count, t_cmd *cmd, t_bashvar **bash)
{
	file->argc = count;
	file->input = STDIN_FILENO;
	file->output = STDOUT_FILENO;
	file->saved_input = dup(STDIN_FILENO);
	file->saved_output = dup(STDOUT_FILENO);
	file->pid = malloc(sizeof(int) * count);
	if (!file->pid)
		return (0);
	ft_pipeline(count, cmd, bash, file);
	dup2(file->saved_input, STDIN_FILENO);
	dup2(file->saved_output, STDOUT_FILENO);
	return (1);
}

/**
  * Coordinates the handling and execution of multiple commands by determining
  * the number of commands in the list , assigning the head command,
  * initializing the file descriptors, and executing the commands
  * @param t_cmd.*cmd
  * @param t_bashvar.**bash
  * @returns void
  */
void	ft_handle_cmd(t_cmd *cmd, t_bashvar **bash)
{
	t_cmd	*head_cmd;
	t_files	*file;
	t_cmd	*head;
	int		count_cmd;

	head_cmd = cmd;
	file = malloc(1 * sizeof(t_files));
	if (!file)
		return ;
	count_cmd = 0;
	head = cmd;
	while (1)
	{
		count_cmd++;
		cmd = cmd->next;
		if (cmd == head)
			break ;
	}
	ft_assign_hd(cmd);
	if (!ft_init_file(file, count_cmd, cmd, bash))
		return ;
	cmd = head_cmd;
	free(file->pid);
	free(file);
}
