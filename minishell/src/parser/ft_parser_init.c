/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser_init.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thibnguy <thibnguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/15 12:26:21 by thibnguy          #+#    #+#             */
/*   Updated: 2023/10/15 12:58:48 by thibnguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
  * Initializes cmd
  * @param t_cmd.**cmd
  * @param t_cmd.**head_cmd
  * @returns void
  */
void	ft_cmd_init(t_cmd **cmd, t_cmd **head_cmd)
{
	*cmd = NULL;
	*head_cmd = *cmd;
}

/**
  * Initializes data
  * @param t_data.**data
  * @param t_data.**head_data
  * @param t_data.**head_pipe
  * @returns void
  */
void	ft_data_init(t_data **data, t_data **head_data, t_data **head_pipe)
{
	*head_data = *data;
	*head_pipe = *head_data;
}

/**
  * Creates command
  * @param t_cmd.**cmd
  * @param t_cmd.**head_cmd
  * @returns void
  */
void	ft_create_cmd(t_cmd **cmd, t_cmd **head_cmd)
{
	addlast_cmd(head_cmd, ft_new_cmd());
	if (*cmd == NULL)
		*cmd = *head_cmd;
	else
		*cmd = (*cmd)->next;
}

/**
  * Sets the after_pipe pointer to the current data element
  * @param t_data.**data
  * @param t_data.**after_pipe
  * @param t_data,**head_pipe
  * @returns void
  */
void	ft_update_ptr(t_data **data, t_data **after_pipe, t_data **head_pipe)
{
	*after_pipe = (*data);
	(*data) = *head_pipe;
}

/**
  * Checks if a data element is NULL or has a non zero exit code
  * @param t_data.**data
  * @param t_cmd.*cmd
  * @returns int
  */
int	ft_check_element(t_data **data, t_cmd *cmd)
{
	if ((*data) == NULL || (*data)->exit_code != 0)
	{
		cmd->command = NULL;
		return (0);
	}
	return (1);
}
