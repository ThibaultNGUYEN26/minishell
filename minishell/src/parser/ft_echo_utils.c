/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thibnguy <thibnguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/15 16:05:43 by thibnguy          #+#    #+#             */
/*   Updated: 2023/10/15 16:50:02 by thibnguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
  * Checks for the whitespace in the current character of the content and
  * decides whether to copy the next element from split or to create a substring
  * from the current position in the content and processes accordingly
  * @param t_data.**data
  * @param t_var.*var
  * @param t_cmd.*cmd
  * @param char.**split
  * @returns int
  */
static int	ft_switch(t_data **data, t_var *var, t_cmd *cmd, char **split)
{
	if (ft_white_space(((*data)->content)[(var->i)]))
	{
		cmd->command[var->j] = ft_strdup(split[var->k]);
		(var->j) += 1;
		(var->k) += 1;
	}
	else
	{
		cmd->command[var->j] = ft_substr((*data)->content, var->ancien, \
			ft_strlen((*data)->content) - var->ancien);
		(var->j) += 1;
		var->test = 1;
		return (1);
	}
	return (0);
}

/**
  * Assists in processing the echo command by handling the case when the
  * character following is not 'n' and manages the extraction of content
  * @param t_data.**data
  * @param t_var.*var
  * @param t_cmd.*cmd
  * @param char.**split
  * @returns int
  */
int	ft_echo_help(t_data **data, t_var *var, t_cmd *cmd, char **split)
{
	var->ancien = var->i;
	(var->i) += 1;
	if (((*data)->content)[var->i] != 'n')
	{
		cmd->command[(var->j)] = ft_substr((*data)->content, var->ancien, \
			ft_strlen((*data)->content) - var->ancien);
		(var->j) += 1;
		var->test = 1;
		return (1);
	}
	while (((*data)->content)[var->i] == 'n')
		(var->i) += 1;
	return (ft_switch(data, var, cmd, split));
}

/**
  * Free split
  * @param char.**s
  * @param int.j
  * @returns void
  */
void	ft_free_split(char **s, int j)
{
	int	i;

	i = 0;
	if (j != -1)
		while (i < j)
			free(s[i++]);
	else
		while (s[i])
			free(s[i++]);
	free(s);
}

/**
  * Handles cases when the command is not echo and copies elements from the
  * split array to the command's argument list
  * @param t_cmd.*cmd
  * @param int.*i
  * @param char.**split
  * @param int.*j
  * @returns void
  */
void	ft_not_echo(t_cmd *cmd, int *i, char **split, int *j)
{
	if (ft_strcmp(split[0], "echo") != 0)
	{
		while (split[*i])
		{
			cmd->command[*j] = ft_strdup(split[*i]);
			*j += 1;
			*i += 1;
		}
	}
}
