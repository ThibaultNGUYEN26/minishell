/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchbouki <rchbouki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 20:30:54 by thibnguy          #+#    #+#             */
/*   Updated: 2023/09/26 21:35:03 by rchbouki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	ft_child(int *pfd, t_files *file)
{
	// close the read end of the pipe in the child process to be sure that the child does not read from it (because it belongs to the parent)
	close(pfd[0]);
	// if the input file is other than the standard input, we duplicate its content into the standard input and close the original one
	if (file->input != STDIN_FILENO)
		dup2(file->input, STDIN_FILENO);
	close(file->input);
	// if the file output is other than the standard output, we duplicate it into the standard output and close the original file
	if (file->output != STDOUT_FILENO)
	{
		dup2(file->output, pfd[1]);
		close(file->output);
	}
	/* // if we are at the last command and the file output is other than the standard output, we duplicate it into the standard output and close the original file
	if (n == 1 && (file->output != STDOUT_FILENO))
	{
		dup2(file->output, STDOUT_FILENO);
		close(file->output);
	} */
	if (file->output == STDOUT_FILENO)
	{
		//printf("Fils : Dupping file_output into pfd[1]\n");
		// if we are not at the last command or the output is the standard output, we duplicate the content of the write end of the pipeline into the standard output and close the write end of the pipeline
		dup2(pfd[1], file->output);
		close(pfd[1]);
	}
}

/* Function that will execute the commands with its options and the env path so we will need it to take as argument :
	- the cmd->command 2D Array 
	- bash->envp 
	And we will need to check if it's builtin or not, so that we execute the builtin instead 
=> cmd will be the string carrying the path it belongs to with a / at the end with the command */
static void	ft_exec_cmd(t_cmd *cmd, t_bashvar **bash)
{
	int		i;
	char	*command;
	char	**path;

	i = -1;
	command = NULL;
	path = ft_find_path((*bash)->envp);
	if (cmd->builtin != NULL)
	{
		(cmd->builtin)(cmd, bash);
		return ;
	}
	if (!path)
	{
		if (access(cmd->command[0], X_OK) == 0)
			if (execve(command, cmd->command, NULL) == -1)
				exit(EXIT_FAILURE);
	}
	else
	{
		while (path[i++])
		{
			command = ft_command(path[i], ft_strlen(cmd->command[0]));
			command = ft_strjoin2(command, cmd->command[0]);
			if (access(command, X_OK) == 0)
				if (execve(command, cmd->command, NULL) == -1)
					exit(EXIT_FAILURE);
			free(command);
		}
	}
}

/* ft_pipeline is the recursive function that will create the children and execute the commands */
static void	ft_pipeline(int n, t_cmd *cmd, t_bashvar **bash, t_files *file)
{
	int		pfd[2];
	int		pid;
	int		status;

	// Check if there is a redirections at the first command so we can fill the file.input or file.output
	//printf("infile : %d, outfile : %d\n", file->input, file->output);
	// Create process of child and the pipes
	ft_redirec_files(cmd, file);
	pid = create_process(pfd, 0);
	if (pid == 0)
	{
		//write(2, "Fils : Into the child !\n", 25);
		ft_child(pfd, file);
		//write(2, "Fils : going into execve\n", 26);
		ft_exec_cmd(cmd, bash);
	}
	else
	{
		//write(2, "Père : Je suis ton père\n", 27);
		close(pfd[1]);
		close(file->input);
		// if last command, we wait for the other children
		if (n == 1)
			while (file->argc--)
				waitpid(-1, &status, 0);
		// Pour passer à la prochaine commande, on doit rediriger le input et output vers les read et write ends of the pipe
		//write(2, "Père : j'ai fini d'attendre\n", 30);
		if (file->input == -1)
			file->input = dup(pfd[0]);
		else
		{
			//write(2, "Père : Dupping file->input into pfd[0]\n", 41);
			dup2(pfd[0], file->input);
		}
		if (file->output == -1)
		{
			file->output = dup(pfd[1]);
			close(pfd[1]);
		}
		close(pfd[0]);
		n--;
		if (n != 0)
			ft_pipeline(n, cmd->next, bash, file);
	}
}

/* The "main" of the execution part */
void    ft_handle_cmd(t_cmd *cmd, t_bashvar **bash)
{
	t_cmd	*head_cmd;
    t_files	*file;
    t_cmd   *head;
    int     count_cmd;

	head_cmd = cmd;
	file = malloc(1 * sizeof(t_files));
	if (!file)
		return ;
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
	// file->argc helps us keep track of the original number of commands
	file->argc = count_cmd;
	ft_pipeline(count_cmd, cmd, bash, file);
	cmd = head_cmd;
	free(file);
}
