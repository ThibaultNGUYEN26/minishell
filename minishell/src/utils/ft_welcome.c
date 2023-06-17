/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_welcome.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thibnguy <thibnguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/17 19:07:56 by thibnguy          #+#    #+#             */
/*   Updated: 2023/06/17 20:14:39 by thibnguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
  * Print welcome text at program's launch.
  * @param void 
  * @returns 0 file open success | 1 file open failed
  */
int	ft_welcome(void)
{
	int		fd;
	char	*line;

	line = NULL;
	fd = open("src/welcome.txt", O_RDONLY);
	if (fd == -1)
	{
		printf("Failed to open the file.\n");
		return (1);
	}
	line = get_next_line(fd);
	while (line)
	{
		printf(MAGENTA"%s"EOC, line);
		free(line);
		line = get_next_line(fd);
	}
	printf("\n\n");
	return (close(fd), 0);
}
