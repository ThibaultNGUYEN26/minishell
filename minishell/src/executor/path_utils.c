/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thibnguy <thibnguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 20:30:47 by thibnguy          #+#    #+#             */
/*   Updated: 2023/09/19 20:30:50 by thibnguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	ft_words(char *s, char c)
{
	int	i;
	int	words;

	if (!s || (int)ft_strlen(s) == 0)
		return (0);
	if (c == 0)
		return (1);
	words = 0;
	i = 0;
	while (s[i] && s[i] == c)
		i++;
	while (s[i])
	{
		while (s[i] != c && s[i])
			i++;
		words++;
		while (s[i] == c && s[i])
			i++;
	}
	return (words);
}

static void	*ft_free(char **res, int j)
{
	while (j >= 0)
		free(res[j--]);
	free(res);
	return (NULL);
}

static char	**ft_fill(char *s, char **res, char c)
{
	int	start;
	int	end;
	int	j;

	start = 0;
	end = 0;
	j = 0;
	while (s[start] && j < ft_words(s, c))
	{
		while (s[start] && s[start] == c)
			start++;
		end = start;
		while (s[end] && s[end] != c)
			end++;
		res[j] = ft_substr_split(s, start, end - start);
		if (!res[j])
			return (ft_free(res, j));
		j++;
		start = end;
	}
	res[j] = NULL;
	return (res);
}

char	**ft_split(char *s, char c)
{
	char	**res;
	int		words;

	if (!s)
		return (NULL);
	words = ft_words(s, c);
	res = malloc((words + 1) * sizeof(char *));
	if (!res)
		return (NULL);
	if (words == 0)
		res[0] = NULL;
	else
		res = ft_fill(s, res, c);
	return (res);
}

char	*ft_strjoin(char *s1, char *s2)
{
	int		i;
	int		j;
	char	*str;

	if (!s1 || !s2)
		return (NULL);
	i = 0;
	j = 0;
	str = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!str)
		return (NULL);
	while (s1[i])
		str[j++] = s1[i++];
	i = 0;
	while (s2[i])
		str[j++] = s2[i++];
	str[j] = '\0';
	free(s1);
	return (str);
}
