/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thibnguy <thibnguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 20:30:54 by thibnguy          #+#    #+#             */
/*   Updated: 2023/10/12 21:25:55 by thibnguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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

/* Function that will execute the commands with its options and the env path so
we will need it to take as argument :
	- the cmd->command 2D Array 
	- bash->envp 
	And we will need to check if it's builtin or not, so that we execute the
	builtin instead 
=> cmd will be the string carrying the path it belongs to with a / at the end
with the command */
static void	ft_exec_cmd(t_files *file, t_cmd *cmd, t_bashvar **bash)
{
	int		i;
	char	*command;
	char	*temp;
	char	**path;

	i = 0;
	command = NULL;
	if (cmd->builtin != NULL && file->argc == 1)
		exit(EXIT_SUCCESS);
	if (cmd->builtin != NULL && file->argc != 1)
		exit((cmd->builtin)(cmd, bash));
	if (access(cmd->command[0], X_OK) == 0)
		if (execve(cmd->command[0], cmd->command, NULL) == -1)
			exit(ft_exec_error("execve"));
	path = ft_find_path((*bash)->envp);
	if (!path)
	{
		if (access(cmd->command[0], X_OK) == 0)
			if (execve(command, cmd->command, NULL) == -1)
				exit(ft_exec_error("execve"));
	}
	else
	{
		while (path[i])
		{
			command = ft_strjoin2(path[i], "/");
			temp = ft_strdup(command);
			free(command);
			command = ft_strjoin2(temp, cmd->command[0]);
			free(temp);
			if (access(command, X_OK) == 0)
				if (execve(command, cmd->command, NULL) == -1)
					exit(ft_exec_error("execve"));
			free(command);
			i++;
		}
		ft_putstr_fd(cmd->command[0], 2);
		ft_putstr_fd(": command not found\n", 2);
		g_exit_code = 127;
		exit(g_exit_code);
	}
}

/* ft_pipeline is the recursive function that will create the children and
execute the commands */
static void	ft_pipeline(int n, t_cmd *cmd, t_bashvar **bash, t_files *file)
{
	int		pfd[2];
	int		pid;
	int		i;
	int		status;
	int		number;

	ft_redirec_files(cmd, file);
	pid = create_process(pfd, 0);
	if (pid == 0)
	{
		ft_child(n, pfd, file);
		if (cmd->command == NULL)
			exit(EXIT_SUCCESS);
		ft_exec_cmd(file, cmd, bash);
	}
	else
	{
		close(pfd[1]);
		close(file->input);
		number = file->argc;
		file->pid[file->argc - n] = pid;
		if (n == 1)
		{
			i = 0;
			while (i < file->argc)
				waitpid(file->pid[i++], &status, 0);
			if (WIFEXITED(status) && WEXITSTATUS(status))
				g_exit_code = WEXITSTATUS(status);
		}
		if (number == 1 && cmd->builtin != NULL && file->input != -1)
		{
			if (file->output != -2)
				dup2(file->output, STDOUT_FILENO);
			g_exit_code = (cmd->builtin)(cmd, bash);
			return ;
		}
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

/* The "main" of the execution part */
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
	file->argc = count_cmd;
	file->input = STDIN_FILENO;
	file->output = STDOUT_FILENO;
	file->saved_input = dup(STDIN_FILENO);
	file->saved_output = dup(STDOUT_FILENO);
	file->pid = malloc(sizeof(int) * count_cmd);
	if (!file->pid)
		return ;
	ft_pipeline(count_cmd, cmd, bash, file);
	dup2(file->saved_input, STDIN_FILENO);
	dup2(file->saved_output, STDOUT_FILENO);
	cmd = head_cmd;
	free(file->pid);
	free(file);
}
