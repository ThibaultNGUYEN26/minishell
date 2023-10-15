/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser_echo.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thibnguy <thibnguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/15 11:40:44 by thibnguy          #+#    #+#             */
/*   Updated: 2023/10/15 16:45:44 by thibnguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
  * Initializes a structure t_var for the echo command
  * @param t_var.*var
  * @param t_cmd.*cmd
  * @param t_data.**data
  * @param char.**s
  * @returns t_var *
  */
static t_var	*ft_init_echo(t_var *var, t_cmd *cmd, t_data **data, char **s)
{
	var = malloc(sizeof(t_var) * 1);
	if (!var)
		return (NULL);
	var->i = 0;
	var->k = 0;
	var->j = 0;
	var->test = 0;
	cmd->command[var->j] = ft_strdup(s[var->k]);
	var->j += 1;
	var->k += 1;
	while (ft_strncmp((*data)->content + var->i, "echo", 3) != 0)
		var->i += 1;
	var->i += 4;
	return (var);
}

/**
  * Checks if a given character is a whitespace
  * @param char.content
  * @returns int
  */
int	ft_white_space(char content)
{
	if (content == '\f' || content == '\t' || content == '\n'
		|| content == '\r' || content == '\v' || content == ' ')
		return (1);
	else
		return (0);
}

/**
  * Completes the echo command by extracting the rest of the content after echo
  * @param t_cmd.*cmd
  * @param t_var.*var
  * @param t_data.**data
  * @param t_data.**head
  * @returns void
  */
static void	ft_echo_end(t_cmd *cmd, t_var *var, t_data **data, t_data **head)
{
	cmd->command[var->j] = ft_substr((*data)->content, var->i, \
		ft_strlen((*data)->content) - var->i);
	while ((*data)->next != *head && (*data)->next->token == 5)
	{
		(*data) = (*data)->next;
		var->temp = ft_strdup(cmd->command[var->j]);
		free(cmd->command[var->j]);
		cmd->command[var->j] = ft_strjoin2(var->temp, (*data)->content);
		free(var->temp);
	}
}

/**
  * Cleans up and returns the value of the variable var->j
  * @param t_var.*var
  * @returns int
  */
static int	ft_echo_return(t_var *var)
{
	int	res;

	res = var->j;
	free(var);
	return (res);
}

/**
  * Processes an echo command with options by splitting it into separate command
  * parts by handling the -n option by merging adjacent parts as long as -n is
  * not followed by non whitespace characters
  * @param t_data.**data
  * @param t_cmd.*cmd
  * @param int.i
  * @param char.**split
  * @param t_data.*head
  * @returns int
  */
int	ft_echo_error(t_data **data, t_cmd *cmd, char **split, t_data *head)
{
	t_var	*var;

	var = NULL;
	var = ft_init_echo(var, cmd, data, split);
	while (1)
	{
		while (((*data)->content)[(var->i)] != '-' \
			&& ft_white_space(((*data)->content)[(var->i)]))
			(var->i) += 1;
		if (((*data)->content)[var->i] == '-')
		{
			if (ft_echo_help(data, var, cmd, split))
				break ;
		}
		else
			break ;
	}
	if (var->test == 1)
		return (ft_echo_return(var));
	while (ft_white_space(((*data)->content)[(var->i)]))
		(var->i) += 1;
	ft_echo_end(cmd, var, data, &head);
	var->j += 1;
	return (ft_echo_return(var));
}
