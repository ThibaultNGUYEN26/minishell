/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thibnguy <thibnguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 19:57:57 by thibnguy          #+#    #+#             */
/*   Updated: 2023/06/27 20:03:52 by thibnguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	*ft_strndup(char *src, int start, int end)
{
	char	*res;
	int		i;

	res = (char *) malloc(sizeof(char) * (end - start + 1));
	if (res == 0)
		return (0);
	i = 0;
	while (i < (end - start))
	{
		res[i] = src[i + start];
		i++;
	}
	res[i] = '\0';
	return (res);
}

static int	ft_is_charset(char c, char *charset)
{
	int	j;
	int	len;

	len = 0;
	while (charset[len])
		len++;
	j = 0;
	while (j < len)
	{
		if (c == charset[j++])
			return (1);
	}
	return (0);
}

static int	ft_count_words(char *str, char *charset)
{
	int	i;
	int	nb_charset;
	int	start;

	i = 0;
	nb_charset = 0;
	while (str[i])
	{
		while (str[i] && ft_is_charset(str[i], charset))
			i++;
		start = i;
		while (str[i] && !ft_is_charset(str[i], charset))
			i++;
		if (i != start)
			nb_charset++;
	}
	return (nb_charset);
}

static void	ft_write_split(char *str, char *charset, char **tab)
{
	int	i;
	int	j;
	int	start;

	i = 0;
	j = 0;
	while (str[i])
	{
		while (str[i] && ft_is_charset(str[i], charset))
			i++;
		start = i;
		while (str[i] && !ft_is_charset(str[i], charset))
			i++;
		if (i != start)
		{
			tab[j] = ft_strndup(str, start, i);
			j++;
		}
	}
}

char	**ft_split(char *str, char *charset)
{
	char	**tab;
	int		nb_words;

	nb_words = ft_count_words(str, charset);
	tab = (char **) malloc(sizeof(char *) * (nb_words + 1));
	if (tab == NULL)
		return (NULL);
	ft_write_split(str, charset, tab);
	tab[nb_words] = 0;
	return (tab);
}