/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thibnguy <thibnguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 19:34:57 by thibnguy          #+#    #+#             */
/*   Updated: 2023/10/15 13:48:22 by thibnguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
  * Checks the validity of a data element in a linked list
  * @param t_data.**data
  * @param t_data.*head_data
  * @returns int
  */
static int	ft_check_data_element(t_data **data, t_data **head_data)
{
	if ((*data) == NULL)
		return (0);
	if ((*data)->token == 5)
		(*data) = (*data)->next;
	if ((*data) == *head_data || (*data)->next == (*data))
		return (0);
	return (1);
}

/**
  * After parses command from input, updates the data pointer to point to the
  * next data element
  * @param t_data.**data
  * @param t_data.*head_data
  * @returns int
  */
static void	ft_update(t_data **data, t_data *after, t_data *head, t_cmd *cmd)
{
	ft_command_parser(cmd, data, after);
	if (after == head)
		(*data) = after;
	else
		(*data) = (after)->next;
}

/**
  * Processes a command by iteratively handling redirections and checking the
  * validity of data elements
  * @param t_cmd.*cmd
  * @param t_data.**data
  * @param t_data.*head_data
  * @param t_data.*head_pipe
  * @returns int
  */
static int	ft_check_redirec(t_cmd *cmd, t_data **data, t_data **h, t_data **p)
{
	int	test;

	while ((*data)->token != 0)
	{
		test = ft_redirec(h, data, cmd, p);
		if (!test)
		{
			cmd->error = 1;
			return (0);
		}
		else if (test == 2)
			break ;
		if (!ft_check_data_element(data, h))
			break ;
	}
	return (1);
}

/**
  * Sets the data pointer back to the head data element and updates the cmd
  * pointer to the head command element
  * @param t_data.**data
  * @param t_data.**h_data
  * @param t_cmd.**cmd
  * @param t_cmd.**h_cmd
  * @returns void
  */
static void	ft_move(t_data **data, t_data **h_data, t_cmd **cmd, t_cmd **h_cmd)
{
	if ((*data) != NULL && (*data)->exit_code != 1 && (*data)->exit_code != 2)
		(*data) = *h_data;
	*cmd = *h_cmd;
}

/**
  * Parses a command strcture by initializing data and command pointers,
  * creating and updating command elements. checking for redirections and
  * elements
  * @param t_data.**data
  * @returns t_cmd *
  */
t_cmd	*ft_parser(t_data **data)
{
	t_data	*head_data;
	t_data	*head_pipe;
	t_data	*after_pipe;
	t_cmd	*head_cmd;
	t_cmd	*cmd;

	ft_cmd_init(&cmd, &head_cmd);
	ft_data_init(data, &head_data, &head_pipe);
	while (1)
	{
		ft_create_cmd(&cmd, &head_cmd);
		if (!ft_check_redirec(cmd, data, &head_data, &head_pipe))
			return (cmd);
		if (!ft_check_element(data, cmd))
			break ;
		ft_update_ptr(data, &after_pipe, &head_pipe);
		ft_update(data, after_pipe, head_data, cmd);
		head_pipe = (*data);
		if ((*data) == head_data)
			break ;
	}
	ft_move(data, &head_data, &cmd, &head_cmd);
	return (cmd);
}
