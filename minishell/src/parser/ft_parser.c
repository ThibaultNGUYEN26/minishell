/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thibnguy <thibnguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 19:34:57 by thibnguy          #+#    #+#             */
/*   Updated: 2023/10/12 20:09:29 by thibnguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/* Si file invalid ou pas de file
	==> on free, on arrete tout et on repart à la minishell loop */
static int	ft_invalid_redirec(t_data **data, t_data *head_data)
{
	if (((*data)->next)->exit_code == 1)
	{
		printf("minishell: syntax error near unexpected token `newline'\n");
		(*data) = head_data;
		(*data)->exit_code = 2;
		g_exit_code = 2;
		return (1);
	}
	if ((*data)->next == head_data)
	{
		printf("minishell: syntax error near unexpected token `newline'\n");
		(*data) = head_data;
		(*data)->exit_code = 2;
		g_exit_code = 2;
		return (1);
	}
	return (0);
}

static int	ft_redirec(t_data **head, t_data **data, t_cmd *cmd, t_data **pipe)
{
	char	**s;
	char	*temp;
	int		i;
	int		j;

	if ((*data)->token != 5)
	{
		if (ft_invalid_redirec(data, *head))
			return (0);
		addlast_node(&(cmd->redirections), ft_data_copy(*data));
		if ((*data) == *head)
			*head = (*data)->next;
		if (*pipe == *data)
			*pipe = (*data)->next;
		ft_delete_element(data);
		(*data) = (*data)->next;
		s = ft_split((*data)->content, "\f\t\n\r\v ");
		addlast_node(&(cmd->redirections), ft_new_stack(ft_strdup(s[0]), NULL));
		j = ft_count_words((*data)->content, "\f\t\n\r\v ");
		if (j == 1)
		{
			if ((*data) == *head)
				*head = (*data)->next;
			if (*pipe == *data)
				*pipe = (*data)->next;
			ft_delete_element(data);
		}
		else
		{
			temp = ft_substr((*data)->content, ft_strlen(s[0]) + 1, \
				ft_strlen((*data)->content) - ft_strlen(s[0]) + 1);
			free((*data)->content);
			(*data)->content = ft_strdup(temp);
			free(temp);
		}
		i = 0;
		while (i < j)
			free(s[i++]);
		free(s);
	}
	return (1);
}

static int	ft_echo_error(t_data **data, t_cmd *cmd, int i, char **split, t_data *head)
{
	int		k;
	int		j;
	int		test;
	char	*temp;
	int		ancien;

	k = 0;
	j = 0;
	test = 0;
	cmd->command[j++] = ft_strdup(split[k++]);
	while (ft_strncmp((*data)->content + i, "echo", 3) != 0)
		i++;
	i += 4;
	while (1)
	{
		while (((*data)->content)[i] != '-' && (((*data)->content)[i] == '\f' \
			|| ((*data)->content)[i] == '\t' || ((*data)->content)[i] == '\n' \
			|| ((*data)->content)[i] == '\r' || ((*data)->content)[i] == '\v' \
			|| ((*data)->content)[i] == ' '))
			i++;
		if (((*data)->content)[i] == '-')
		{
			ancien = i;
			i++;
			if (((*data)->content)[i] != 'n')
			{
				cmd->command[j++] = ft_substr((*data)->content, ancien, \
					ft_strlen((*data)->content) - ancien);
				test = 1;
				break ;
			}
			while (((*data)->content)[i] == 'n')
				i++;
			if (((*data)->content)[i] == '\f' || ((*data)->content)[i] == '\t' \
				|| ((*data)->content)[i] == '\n' \
				|| ((*data)->content)[i] == '\r' \
				|| ((*data)->content)[i] == '\v' \
				|| ((*data)->content)[i] == ' ')
				cmd->command[j++] = ft_strdup(split[k++]);
			else
			{
				cmd->command[j++] = ft_substr((*data)->content, ancien, \
					ft_strlen((*data)->content) - ancien);
				test = 1;
				break ;
			}
		}
		else
			break ;
	}
	if (test == 1)
		return (j);
	while (((*data)->content)[i] == '\f' || ((*data)->content)[i] == '\t' \
		|| ((*data)->content)[i] == '\n' || ((*data)->content)[i] == '\r' \
		|| ((*data)->content)[i] == '\v' || ((*data)->content)[i] == ' ')
		i++;
	cmd->command[j] = ft_substr((*data)->content, i, \
		ft_strlen((*data)->content) - i);
	while ((*data)->next != head && (*data)->next->token == 5)
	{
		(*data) = (*data)->next;
		temp = ft_strdup(cmd->command[j]);
		free(cmd->command[j]);
		cmd->command[j] = ft_strjoin2(temp, (*data)->content);
		free(temp);
	}
	j++;
	return (j);
}

static void	ft_command_parser(t_cmd *cmd, t_data **data, t_data *after_pipe)
{
	char	**split;
	t_data	*head;
	int		i;
	int		j;

	i = 0;
	j = 0;
	head = *data;
	while (1)
	{
		i += ft_count_words((*data)->content, "\f\t\n\r\v ");
		*data = (*data)->next;
		if ((*data) == after_pipe)
			break ;
	}
	if (i == 0)
	{
		cmd->command = NULL;
		return ;
	}
	cmd->command = malloc(sizeof(char *) * (i + 2));
	if (!cmd->command)
		return ;
	(*data) = head;
	while (1)
	{
		if (ft_count_words((*data)->content, "\f\t\n\r\v ") != 0)
		{
			i = 0;
			split = ft_split((*data)->content, "\f\t\n\r\v ");
			if (ft_strcmp(split[0], "echo") == 0)
				j = ft_echo_error(data, cmd, i, split, after_pipe);
			else
				while (split[i])
					cmd->command[j++] = ft_strdup(split[i++]);
			i = 0;
			while (split[i])
				free(split[i++]);
			free(split);
		}
		if ((*data) == after_pipe)
			break ;
		*data = (*data)->next;
		if ((*data) == after_pipe)
			break ;
	}
	cmd->command[j] = NULL;
}

t_cmd	*ft_parser(t_data **data)
{
	t_data	*head_data;
	t_data	*head_pipe;
	t_data	*after_pipe;
	t_cmd	*head_cmd;
	t_cmd	*cmd;

	cmd = NULL;
	head_data = *data;
	head_pipe = head_data;
	head_cmd = cmd;
	while (1)
	{
		addlast_cmd(&head_cmd, ft_new_cmd());
		if (cmd == NULL)
			cmd = head_cmd;
		else
			cmd = (cmd)->next;
		while ((*data)->token != 0)
		{
			if (!ft_redirec(&head_data, data, cmd, &head_pipe))
			{
				cmd->error = 1;
				return (cmd);
			}
			if ((*data) == NULL)
				break ;
			(*data) = (*data)->next;
			if ((*data) == head_data || (*data)->next == (*data))
				break ;
		}
		if ((*data) == NULL || (*data)->exit_code != 0)
		{
			cmd->command = NULL;
			break ;
		}
		after_pipe = (*data);
		(*data) = head_pipe;
		ft_command_parser(cmd, data, after_pipe);
		if (after_pipe == head_data)
			(*data) = after_pipe;
		else
			(*data) = (after_pipe)->next;
		head_pipe = (*data);
		if ((*data) == head_data)
			break ;
	}
	if ((*data) != NULL && (*data)->exit_code != 1 && (*data)->exit_code != 2)
		(*data) = head_data;
	cmd = head_cmd;
	return (cmd);
}
