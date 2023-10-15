/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thibnguy <thibnguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/15 11:41:49 by thibnguy          #+#    #+#             */
/*   Updated: 2023/10/15 16:43:00 by thibnguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
  * Initializes integer variable i and j and sets the head pointer to the
  * current data pointer
  * @param int.*i
  * @param int.*j
  * @param t_data.**data
  * @param t_data.**head
  * @returns void
  */
static void	ft_init_var1(int *i, int *j, t_data **data, t_data **head)
{
	*i = 0;
	*j = 0;
	*head = *data;
}

/**
  * Allocates memory for the cmd->command array based on the calculated size i
  * @param t_cmd.*cmd
  * @param t_data.**data
  * @param t_data.**head
  * @param int.i
  * @returns void
  */
static void	ft_init_var2(t_cmd *cmd, t_data **data, t_data **head, int i)
{
	cmd->command = malloc(sizeof(char *) * (i + 2));
	if (!cmd->command)
		return ;
	(*data) = *head;
}

/**
  * Counts how many elements will be in cmd->command
  * @param t_data.**data
  * @param t_data.**after_pipe
  * @param t_cmd.*cmd
  * @returns int
  */
static int	ft_count_options(t_data **data, t_data **after, t_cmd *cmd, int *i)
{
	while (1)
	{
		*i += ft_count_words((*data)->content, "\f\t\n\r\v ");
		*data = (*data)->next;
		if ((*data) == *after)
			break ;
	}
	if (*i == 0)
	{
		cmd->command = NULL;
		return (0);
	}
	return (1);
}

/**
  * Checks if the current data pointer has reached the after_pipe pointer
  * @param t_data.**data
  * @param t_data.**after_pipe
  * @returns int
  */
static int	ft_conditions(t_data **data, t_data **after_pipe)
{
	if ((*data) == *after_pipe)
		return (1);
	*data = (*data)->next;
	if ((*data) == *after_pipe)
		return (1);
	return (0);
}

/**
  * Parses a command by counting options/arguments, initializing memory for
  * cmd->command
  * @param t_cmd.*cmd
  * @param t_data.**data
  * @param t_data.**after_pipe
  * @returns void
  */
void	ft_command_parser(t_cmd *cmd, t_data **data, t_data *after_pipe)
{
	char	**split;
	t_data	*head;
	int		i;
	int		j;

	ft_init_var1(&i, &j, data, &head);
	if (!ft_count_options(data, &after_pipe, cmd, &i))
		return ;
	ft_init_var2(cmd, data, &head, i);
	while (1)
	{
		if (ft_count_words((*data)->content, "\f\t\n\r\v ") != 0)
		{
			i = 0;
			split = ft_split((*data)->content, "\f\t\n\r\v ");
			if (ft_strcmp(split[0], "echo") == 0)
				j = ft_echo_error(data, cmd, split, after_pipe);
			ft_not_echo(cmd, &i, split, &j);
			ft_free_split(split, -1);
		}
		if (ft_conditions(data, &after_pipe))
			break ;
	}
	cmd->command[j] = NULL;
}
