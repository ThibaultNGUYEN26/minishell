/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtins_error.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thibnguy <thibnguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 16:30:51 by thibnguy          #+#    #+#             */
/*   Updated: 2023/10/11 23:39:32 by thibnguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void    ft_builtin_error(char *cmd)
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
		exit_code = 14;
	}
    else if (errno == EINVAL)
	{
		exit_code = 22;
	}
    else if (errno == ENOMEM)
	{
		exit_code = 12;
	}
    else if (errno == ERANGE)
	{
		exit_code = 34;
	}
	else
	{
		str = ft_strjoin2(temp, ": Error opening file\n");

	}
	free(temp);
	ft_putstr_fd(str, 2);
	free(str);
}
