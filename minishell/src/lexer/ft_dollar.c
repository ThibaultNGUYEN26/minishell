/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dollar.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thibnguy <thibnguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 18:44:33 by thibnguy          #+#    #+#             */
/*   Updated: 2023/10/07 19:38:48 by thibnguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	ft_equal(char **envp, char **res, char *dollar, int j)
{
	char	*temp;

	temp = NULL;
	while (envp[j]
		&& ft_strncmp(envp[j], dollar, ft_strchr(envp[j], '=')))
		j++;
	// if the envp exists we join it to res, sinon we just ignore it
	if (envp[j])
	{
		temp = ft_strdup(*res);
		free(*res);
		*res = ft_strjoin2(temp, envp[j] + ft_strlen(dollar) + 1);
		free(temp);
	}
}

/**
	* Manage all expender case of $
	* @param data
	* @param envp
	* @returns char *
	*/
static char	*ft_dollar_utils(t_data *data, char **envp)
{
	char	*res;
	char	*dollar;
	int		j;
	int		i;

	i = 0;
	// get how many $ there are and save the last position
	j = ft_strchr(data->content, '$') + 1;
	// on met ce qu'il y avait avant le dollar dans res
	res = ft_substr(data->content, i, j - 1);
	while (data->content[i] && ft_strchr(data->content + i, '$') != -1)
	{
		j = ft_strchr(data->content + i, '$') + i + 1;
		if (i != 0)
			res = ft_strjoin(res, ft_substr(data->content + i, 0, j - i - 1));
		i = j;
		// i = jusqu'à où la variable $ va
		//(exemple : $PATH' ici elle s'arrête à ')
		while (data->content[i] && data->content[i] != ' '
			&& data->content[i] != '\'' && data->content[i] != '\"'
			&& data->content[i] != '$')
			i++;
		dollar = ft_substr(data->content, j, i - j);
		if (data->content[j] == '!' || data->content[j] == '@'
			|| data->content[j] == '*'
			|| (data->content[j] >= '0' && data->content[j] <= '9'))
			res = ft_strjoin(res, ft_substr(data->content, j + 1, i - j - 1));
		else if (data->content[j] == '?')
			res = ft_strjoin(res, ft_substr(data->content, j - 1, i - j + 1));
		else if (data->content[j] == '%' || data->content[j] == '^'
			|| data->content[j] == '=' || data->content[j] == '+'
			|| data->content[j] == '.' || data->content[j] == '/'
			|| data->content[j] == ',')
			res = ft_strjoin(res, ft_substr(data->content, j, i - j));
		else if (data->content[j] == '#')
		{
			res = ft_strjoin(res, "0");
			res = ft_strjoin(res, ft_substr(data->content, j + 1, i - j - 1));
		}
		else if (data->content[j] == '\\' || data->content[j] == '~')
		{
			res = ft_strjoin(res, "$");
			res = ft_strjoin(res, ft_substr(data->content, j + 1, i - j - 1));
		}
		else if (data->content[j] != '_')
		{
			{
				j = 0;
				ft_equal(envp, &res, dollar, j);
				if (data->content[i] == '$')
				{
					i++;
					res = ft_strjoin(res, "$");
				}
			}
		}
		free(dollar);
	}
	// adding if there is something after
	res = ft_strjoin(res, \
	ft_substr(data->content, i, ft_strlen(data->content)));
	return (res);
}

/**
	* Check if there is a dollar in command
	* @param data
	* @param envp
	* @returns void
	*/
void	ft_dollar(t_data *data, char **envp)
{
	t_data	*head;
	char	*res;

	head = data;
	while (1)
	{
		// si c'est un mot (donc not a token) et qu'il contient un $
		if (data->token == 5 && ft_strchr(data->content, '$') != -1)
		{
			res = ft_dollar_utils(data, envp);
			free(data->content);
			data->content = ft_strdup(res);
			free(res);
		}
		break ;
		if (data->next == head)
			break ;
		data = data->next;
	}
}
