/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_error.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchbouki <rchbouki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 16:30:51 by thibnguy          #+#    #+#             */
/*   Updated: 2023/10/12 00:51:55 by rchbouki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_exec_error(char *cmd)
{
	char	*str;
	char	*temp;

	str = ft_strjoin2("minishell: ", cmd);
	temp = ft_strdup(str);
	free(str);
	if (errno == ENOENT)
	{
		str = ft_strjoin2(temp, ": No such file or directory\n");
		exit_code = 2;
	}
	else if (errno == EACCES)
	{
		str = ft_strjoin2(temp, ": Permission denied\n");
		exit_code = 13;
	}
	else if (errno == EFAULT)
	{
		str = ft_strjoin2(temp, ": Segmentation fault, bad address\n");
		exit_code = 14;
	}
	else if (errno == EINVAL)
	{
		str = ft_strjoin2(temp, ": Invalid argument\n");
		exit_code = 22;
	}
	else if (errno == ENOMEM)
	{
		str = ft_strjoin2(temp, ": Couldn't allocate memory\n");
		exit_code = 12;
	}
	free(temp);
	ft_putstr_fd(str, 2);
	free(str);
	return (exit_code);
}
