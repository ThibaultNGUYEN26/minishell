/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thibnguy <thibnguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 23:54:58 by thibnguy          #+#    #+#             */
/*   Updated: 2023/10/15 13:15:33 by thibnguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/**
  * Constructs the full path of an executable command by concatenating the path
  * and the cmd strings
  * @param char.*path
  * @param char.*cmd
  * @returns char *
  */
static char	*ft_find_cmd(char *path, char *cmd)
{
	char	*command;
	char	*temp;

	command = ft_strjoin2(path, "/");
	temp = ft_strdup(command);
	free(command);
	command = ft_strjoin2(temp, cmd);
	free(temp);
	return (command);
}

/**
  * Attempts to execute a command when no path is provided by checking if it's
  * executable
  * @param char.*cmd
  * @returns void
  */
static void	ft_no_path(t_cmd *cmd)
{
	char	*command;

	command = NULL;
	if (access(cmd->command[0], X_OK) == 0)
	{
		if (execve(command, cmd->command, NULL) == -1)
			exit(ft_exec_error("execve"));
	}
	else
		exit(EXIT_FAILURE);
}

/**
  * Searches for an executable command in the provided path array and attemps to
  * execute it
  * @param char.**path
  * @param t_cmd.*cmd
  * @returns void
  */
void	ft_execve_utils(char **path, t_cmd *cmd)
{
	char	*command;
	int		i;

	i = -1;
	command = NULL;
	if (!path)
		ft_no_path(cmd);
	else
	{
		while (path[++i])
		{
			command = ft_find_cmd(path[i], cmd->command[0]);
			if (access(command, X_OK) == 0)
				if (execve(command, cmd->command, NULL) == -1)
					exit(ft_exec_error("execve"));
			free(command);
		}
		ft_putstr_fd(cmd->command[0], 2);
		ft_putstr_fd(": command not found\n", 2);
		exit(127);
	}	
}

/**
  * Handles the execution of builtin commands in the parent process
  * @param t_files.*file
  * @param t_cmd.*cmd
  * @param t_bashvar.**bash
  * @returns int
  */
int	ft_builtin_parent(t_files *file, t_cmd *cmd, t_bashvar **bash)
{
	close(file->input);
	if (file->argc == 1 && cmd->builtin != NULL && file->input != -1)
	{
		if (file->output != -2)
			dup2(file->output, STDOUT_FILENO);
		g_exit_code = (cmd->builtin)(cmd, bash);
		return (1);
	}
	return (0);
}

/**
  * Manages the execution of commands in the parent process by waiting for
  * child processes to complete and updating the global exit code variable
  * @param t_files.*file
  * @param int.n
  * @param int.pid
  * @param t_cmd.*cmd
  * @returns void
  */
void	ft_parent_exec(t_files *file, int n, int pid, t_cmd *cmd)
{
	int	i;
	int	status;

	i = 0;
	file->pid[file->argc - n] = pid;
	if (n == 1 && cmd->command)
	{
		i = 0;
		while (i < file->argc)
			waitpid(file->pid[i++], &status, 0);
		if (g_exit_code != 0 && !WEXITSTATUS(status))
			g_exit_code = 0;
		else if (WIFEXITED(status) && WEXITSTATUS(status))
			g_exit_code = WEXITSTATUS(status);
	}
}
