/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thibnguy <thibnguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 17:18:29 by thibnguy          #+#    #+#             */
/*   Updated: 2023/10/09 19:14:16 by thibnguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_env(t_cmd *cmd, t_bashvar **bash)
{
	(void)cmd;
	int	i;

	i = 0;
	while ((*bash)->envp[i])
		printf("%s\n", (*bash)->envp[i++]);
	exit_code = 0;
	return (EXIT_SUCCESS);
}
