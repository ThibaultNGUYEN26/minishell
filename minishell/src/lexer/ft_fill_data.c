/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fill_data.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thibnguy <thibnguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 21:03:08 by thibnguy          #+#    #+#             */
/*   Updated: 2023/07/04 18:23:06 by thibnguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
  * Fill linked list with the user input.
  * @param input
  * @returns data
  */
t_data	*ft_fill_data(char *input, char **envp)
{
	t_data	*data;
	char	**tab;
	int		i;

	(void)envp;
	tab = NULL;
	data = NULL;
	tab = ft_split(input, " ");
	i = -1;
	while (tab[++i])
		addlast_node(&data, ft_new_stack(tab[i]));
	free(tab);
	return (data);
}

/* static char	*ft_env_content(char *input, char **envp)
{
	char	*element;
	char	*var;
	int		i;

	i = 0;
	while (input[i] != ' ' && input[i])
		i++;
	var = ft_substr(input, 0, i);
	while (*envp && ft_strncmp(*envp, var, ft_strlen(var)))
		envp++;
	if (*envp)
		element = *envp + ft_strlen(var) + 1;
	else
		element = "\0";
	return (element);
}

t_data	*ft_fill_data(char *input, char **envp)
{
	t_data	*data;
	char	c;
	int		i;
	int		j;
	
	i = 0;
	data = NULL;
	while (i < ft_strlen(input))
	{
		j = i;
		if (input[i] == '<' || input[i] == '>' || input[i] == '|')
			addlast_node(&data, ft_new_stack(ft_substr(input, i, 1)));
		else if (!ft_strncmp(input + i, ">>", 2) || !ft_strncmp(input + i, "<<", 2))
			addlast_node(&data, ft_new_stack(ft_substr(input, i, 2)));
		else if (input[i] == '\"' || input[i] == '\'')
		{
			c = input[i];
			printf("%d\n", i);
			while (input[++j] && input[j] != c);
			printf("%d\n", j);
			if (!input[j])
			{
				printf("Error\n");
				exit(0);
			}
			addlast_node(&data, ft_new_stack(ft_substr(input, i + 1, j - i - 1)));
			i = j + 1;
			printf("%s\n", input + i);
		}
		else if (input[i] == ' ')
			i++;
		else
		{
			if (input[i] == '$')
			{
				if (input[i + 1] == '?')
				{
					addlast_node(&data, ft_new_stack("$?"));
					i += 2;
				}
				else
				{
					addlast_node(&data, ft_new_stack(ft_env_content(input + i + 1, envp)));
					while (input[i] && input[i] != ' ')
						i++;
				}
			}
			else
			{
				while (input[j] && input[j] != ' ')
					j++;
				addlast_node(&data, ft_new_stack(ft_substr(input, i, j - i)));
				i = j + 1;
			}
		}
	}
	return (data);
} */