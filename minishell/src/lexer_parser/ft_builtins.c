/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtins.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchbouki <rchbouki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 17:33:45 by thibnguy          #+#    #+#             */
/*   Updated: 2023/08/21 22:05:21 by rchbouki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	ft_builtins_status(t_data *data)
{
	if (ft_strncmp(data->content, "cd", 2) == 0 || ft_strncmp(data->content, " cd", 3) == 0)
		data->builtins = ft_strdup("cd");
	else if (ft_strncmp(data->content, "echo", 4) == 0 || ft_strncmp(data->content, " echo", 5) == 0)
		data->builtins = ft_strdup("echo");
	else if (ft_strncmp(data->content, "env", 3) == 0 || ft_strncmp(data->content, " env", 4) == 0)
		data->builtins = ft_strdup("env");
	else if (ft_strncmp(data->content, "export", 6) == 0 || ft_strncmp(data->content, " export", 7) == 0)
		data->builtins = ft_strdup("export");
	else if (ft_strncmp(data->content, "pwd", 3) == 0 || ft_strncmp(data->content, " pwd", 4) == 0)
		data->builtins = ft_strdup("pwd");
	else if (ft_strncmp(data->content, "unset", 5) == 0 || ft_strncmp(data->content, " unset", 6) == 0)
		data->builtins = ft_strdup("unset");
	else
		data->builtins = ft_strdup("NULL");
}

static int	ft_count_pipe(char *input)
{
	char	**tab;
	int		i;
	int		j;

	i = -1;
	j = 0;
	tab = ft_split(input, " ");
	while (tab[++i])
		if (ft_strcmp(tab[i], "|") == 0)
			j++;
	return (j);
}

void	ft_builtins(t_data *data, char *input)
{
	t_data	*head;
	int		pipe;
	int		nb_pipes;

	nb_pipes = ft_count_pipe(input);
	head = data;
	pipe = 0;
	while (1)
	{
		if (data->token != 5)
		{
			if (data->token == 0)
				pipe++;
			data->builtins = NULL;
			data = data->next;
		}
		ft_builtins_status(data);
		printf("%s\n", data->builtins);
		if (data->next == head || pipe > nb_pipes)
			break ;
		data = data->next;
	}
	data = head;
}