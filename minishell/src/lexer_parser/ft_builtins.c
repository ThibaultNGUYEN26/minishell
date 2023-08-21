/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtins.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thibnguy <thibnguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 17:33:45 by thibnguy          #+#    #+#             */
/*   Updated: 2023/08/21 18:32:14 by thibnguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	ft_check_builtins(char **tab, int i)
{
	if (ft_strcmp(tab[i], "cd") == 0
		|| ft_strcmp(tab[i], "echo") == 0
		|| ft_strcmp(tab[i], "env") == 0
		|| ft_strcmp(tab[i], "export") == 0
		|| ft_strcmp(tab[i], "pwd") == 0
		|| ft_strcmp(tab[i], "unset") == 0)
		return (1);
	return (0);
}

void	ft_builtins(t_data *data, char *input)
{
	char	**tab;
	int		i;

	(void)data;
	tab = ft_split(input, " ");
	if (ft_check_builtins(tab, 0))
		printf("builtins : %s\n", tab[0]);
	i = -1;
	while (tab[++i])
	{
		if (ft_strcmp(tab[i], "|") == 0)
			if (ft_check_builtins(tab, i + 1))
				printf("builtins : %s\n", tab[i + 1]);
	}
}
