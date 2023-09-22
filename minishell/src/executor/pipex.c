/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchbouki <rchbouki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 20:30:54 by thibnguy          #+#    #+#             */
/*   Updated: 2023/09/21 14:45:56 by rchbouki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	ft_child(int *pfd, int n, t_files file)
{
	close(pfd[0]);
	if (file.input != STDIN_FILENO)
	{
		dup2(file.input, STDIN_FILENO);
		close(file.input);
	}
	if (n == 1 && (file.output != STDOUT_FILENO))
	{
		dup2(file.output, STDOUT_FILENO);
		close(file.output);
	}
	else
	{
		dup2(pfd[1], STDOUT_FILENO);
		close(pfd[1]);
	}
	if (n == file.argc && file.input == -1)
		exit(0);
}

/* Function that will execute the commands with its options and the env path so we will need it to take as argument :
	- the cmd->command 2D Array 
	- bash->envp 
	And we will need to check if it's builtin or not, so that we execute the builtin instead 
=> cmd will be the string carrying the path it belongs to with a / at the end with the command */
static void	ft_exec_cmd(char **command, char **envp)
{
	int		i;
	char	*cmd;

	i = -1;
	if (!envp)
	{
		if (access(command[0], X_OK) == 0)
			if (execve(NULL, command, NULL) == -1)
				exit(EXIT_FAILURE);
	}
	else
	{
		while (envp[++i])
		{
			cmd = ft_command(envp[i], ft_strlen(command[0]));
			cmd = ft_strjoin(cmd, command[0]);
			if (access(cmd, X_OK) == 0)
				if (execve(cmd, command, NULL) == -1)
					exit(EXIT_FAILURE);
		}
	}
}

/* ft_pipeline is the recursive function that will create the children and execute the commands */
static void	ft_pipeline(int n, t_cmd *cmd, t_bashvar *bash, t_files file)
{
	int		pfd[2];
	int		pid;
	int		status;

	pid = create_process(n, pfd, 0);
	if (pid == 0)
	{
		ft_child(pfd, n, file);
		ft_exec_cmd(*argv, path);
	}
	else
	{
		close(pfd[1]);
		close(file.input);
		if (n == 1)
			while (file.argc--)
				waitpid(-1, &status, 0);
		if (file.input == -1)
			file.input = dup(pfd[0]);
		else
			dup2(pfd[0], file.input);
		close(pfd[0]);
		if (n != 0)
			ft_pipeline(n - 1, argv + 1, file, path);
	}
}

static void	ft_open_errors(char *filename)
{
	if (errno == ENOENT)
		printf("File '%s' does not exist.\n", filename);
	else if (errno == EACCES)
		printf("Permission denied for file '%s'.\n", filename);
	else
		printf("Error opening file '%s'. Error code: %d.\n", filename, errno);
}

/* The "main" of the execution part */
void    ft_handle_cmd(t_cmd *cmd, t_bashvar *bash)
{
    t_files	file;
    t_cmd   *head;
    int     count_cmd;

    // count_cmd is the number of commands there are
    count_cmd = 0;
    head = cmd;
    while (1)
    {
        count_cmd++;
        cmd = cmd->next;
        if (cmd == head)
            break;
    }
	// Check if there is a redirections at the first command so we can fill the file.input 
	if (cmd->redirections != NULL)
	{
		if ((cmd->redirections)->token == 1 || (cmd->redirections)->token == 4)
			file.input = open((cmd->redirections)->next->content, O_RDONLY);
	}
	ft_pipeline(count_cmd, cmd, bash, file);
}
