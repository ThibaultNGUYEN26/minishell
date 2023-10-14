/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_thibnguy.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thibnguy <thibnguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 15:49:10 by thibnguy          #+#    #+#             */
/*   Updated: 2023/10/14 19:15:41 by thibnguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
  * Read the entire file
  * @param char.*file
  * @returns char *
  */
char	*ft_read(char *file)
{
	int		fd;
	char	*file_content;
	int		bytes_read;

	fd = open(file, O_RDONLY);
	if (fd == -1)
	{
		printf("Failed to open the file.\n");
		return (NULL);
	}
	file_content = (char *)malloc(4966 + 1);
	bytes_read = read(fd, file_content, 4966);
	if (bytes_read == -1)
	{
		perror("Failed to read the file");
		close(fd);
		free(file_content);
		return (NULL);
	}
	file_content[bytes_read] = '\0';
	close(fd);
	return (file_content);
}

/**
  * Displays the file
  * command
  * @param t_cmd.*cmd
  * @param t_bashvar.**bash
  * @returns int
  */
int	ft_thibnguy(t_cmd *cmd, t_bashvar **bash)
{
	char	*file;

	(void)cmd;
	(void)bash;
	file = ft_read("src/thibnguy.txt");
	printf(MAGENTA"%s\n"EOC, file);
	free(file);
	return (0);
}
