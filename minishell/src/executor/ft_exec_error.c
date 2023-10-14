/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_error.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thibnguy <thibnguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 16:30:51 by thibnguy          #+#    #+#             */
/*   Updated: 2023/10/14 18:58:29 by thibnguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
	* Manages exit_code
	* @param char.*temp
	* @returns char *
	*/
static char	*ft_exit_code1(char *temp)
{
	char	*str;

	str = NULL;
	if (errno == ENOENT)
	{
		str = ft_strjoin2(temp, ": No such file or directory\n");
		g_exit_code = 2;
	}
	else if (errno == EACCES)
	{
		str = ft_strjoin2(temp, ": Permission denied\n");
		g_exit_code = 13;
	}
	else if (errno == EFAULT)
	{
		str = ft_strjoin2(temp, ": Segmentation fault, bad address\n");
		g_exit_code = 14;
	}
	return (str);
}

/**
	* Manages exit_code
	* @param char.*temp
	* @returns char *
	*/
static char	*ft_exit_code2(char *temp)
{
	char	*str;

	str = NULL;
	if (errno == EINVAL)
	{
		str = ft_strjoin2(temp, ": Invalid argument\n");
		g_exit_code = 22;
	}
	else if (errno == ENOMEM)
	{
		str = ft_strjoin2(temp, ": Couldn't allocate memory\n");
		g_exit_code = 12;
	}
	return (str);
}

/**
	* Manages error messages and exit_code
	* @param char.*temp
	* @returns int
	*/
int	ft_exec_error(char *cmd)
{
	char	*str;
	char	*temp;

	str = ft_strjoin2("minishell: ", cmd);
	temp = ft_strdup(str);
	free(str);
	str = ft_exit_code1(temp);
	if (str == NULL)
		str = ft_exit_code2(temp);
	if (str == NULL)
		g_exit_code = 0;
	ft_putstr_fd(str, 2);
	free(temp);
	free(str);
	return (g_exit_code);
}
