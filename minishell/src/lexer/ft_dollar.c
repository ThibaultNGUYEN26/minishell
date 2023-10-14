/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dollar.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thibnguy <thibnguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 18:44:33 by thibnguy          #+#    #+#             */
/*   Updated: 2023/10/14 18:56:26 by thibnguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
	* Manage all expender case of $
	* @param char.**envp
	* @param int.i
	* @param int.j
	* @param t_data.*data
	* @returns char *
	*/
static char	*ft_equal(char **envp, int i, int j, t_data *data)
{
	char	*res;
	char	*dollar;
	int		k;

	k = 0;
	res = NULL;
	dollar = ft_substr(data->content, j, i - j);
	while (envp[k]
		&& ft_strncmp(envp[k], dollar, ft_strchr(envp[k], '=')))
		k++;
	if (envp[k])
		res = ft_strdup(envp[k] + ft_strlen(dollar) + 1);
	free(dollar);
	return (res);
}

/**
	* Manage all expender case of $
	* @param t_data.*data
	* @param char.**envp
	* @returns char *
	*/
static char	*ft_dollar_utils(t_data *data, char **envp)
{
	char	*res;
	char	*temp;
	int		j;
	int		i;

	temp = NULL;
	ft_dollar_init(data, &i, &j, &res);
	while (data->content[i] && ft_strchr(data->content + i, '$') != -1)
	{
		if (!ft_norminette(&i, &j, data, &res))
		{
			if (!ft_question_mark(data->content, &res, i, j))
			{
				temp = ft_equal(envp, i, j, data);
				if (temp)
					res = ft_strjoin(res, temp);
				i = ft_check_dollar(data->content[i], &res, i);
			}
		}
	}
	res = ft_strjoin(res, \
	ft_substr(data->content, i, ft_strlen(data->content)));
	return (res);
}

/**
	* Check if there is a dollar in command
	* @param t_data.*data
	* @param char.**envp
	* @returns void
	*/
void	ft_dollar(t_data *data, char **envp)
{
	t_data	*head;
	char	*res;

	head = data;
	while (1)
	{
		if (data->token == 5 && ft_strchr(data->content, '$') != -1)
		{
			res = ft_dollar_utils(data, envp);
			free(data->content);
			data->content = ft_strdup(res);
			free(res);
		}
		if (data->next == head)
			break ;
		data = data->next;
	}
}
