/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thibnguy <thibnguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/17 18:42:28 by thibnguy          #+#    #+#             */
/*   Updated: 2023/10/14 13:02:26 by thibnguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
  * Extracts a substring from s starting from start to len and puts it in tab[]
  * @param char.*s
  * @param int.start
  * @param int.len
  * @returns char *
  */
char	*ft_substr(char *s, int start, int len)
{
	int		i;
	int		j;
	char	*tab_var;

	if (!s)
		return (NULL);
	if (start >= ft_strlen(s))
		return (ft_strdup(""));
	if (ft_strlen(s + start) < len)
		len = ft_strlen(s + start);
	tab_var = malloc((sizeof(char) * len + 1));
	if (!tab_var)
		return (NULL);
	i = -1;
	j = 0;
	while (s[++i])
		if (i >= start && j < len)
			tab_var[j++] = s[i];
	tab_var[j] = '\0';
	return (tab_var);
}
