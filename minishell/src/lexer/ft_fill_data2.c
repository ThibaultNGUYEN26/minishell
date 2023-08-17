/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fill_data.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thibnguy <thibnguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 21:03:08 by thibnguy          #+#    #+#             */
/*   Updated: 2023/08/17 16:59:41 by thibnguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
  * Fill linked list with the user input.
  * @param input
  * @returns data
  */
/* t_data   *ft_fill_data(char *input, char **envp)
{
    t_data  *data;
    char    **tab;
    int     i;

    (void)envp;
    tab = NULL;
    data = NULL;
    tab = ft_split(input, " ");
    i = -1;
    while (tab[++i])
        addlast_node(&data, ft_new_stack(tab[i]));
    free(tab);
    return (data);
} */

static char *ft_simple_quotes(char *input, int *i)
{
    char    *res;
    int     j = *i;
    char    c;
    
    res = NULL;
    c = input[*i];
    while (input[++j] && input[j] != c);
    if (!input[j])
    {
        printf("Error\n");
        exit(0);
    }
    res = ft_substr(input, *i + 1, j - *i - 1);
    *i = j + 1;
    return (res);
}

static char *ft_env_content(char *input, char **envp)
{
    char    *element;
    char    *var;
    int     i;

    i = 0;
    while ((input[i] != ' ' || input[i] != '\'' || input[i] != '\"') && input[i])
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

static char *ft_dollar_sign(char *input, int *i, char **envp)
{
    char    *res;
    
    res = NULL;
    if (input[*i + 1] == '?')
    {
        res = "$?";
        *i += 2;
    }
    else if (input[*i + 1] == ' ' || input[*i + 1] == '\0')
    {
        res = "$";
        *i += 1;
    }
    else if (input[*i + 1] == '\'' || input[*i + 1] == '\"')
        *i += 1;
    else
    {
        res = ft_env_content(input + (*i) + 1, envp);
        while (input[*i] && input[*i] != ' ')
            *i += 1;
    }
    return (res);
}

t_data  *ft_fill_data(char *input, char **envp)
{
    t_data  *data;
    char    *res;
    int     i;
    int     j;

    i = 0;
    data = NULL;
    while (i < ft_strlen(input))
    {
        j = i;
        if (input[i] == '<' || input[i] == '>' || input[i] == '|')
            addlast_node(&data, ft_new_stack(ft_substr(input, i, 1)));
        else if (!ft_strncmp(input + i, ">>", 2) || !ft_strncmp(input + i, "<<", 2))
            addlast_node(&data, ft_new_stack(ft_substr(input, i, 2)));
        else if (input[i] == '\'')
            addlast_node(&data, ft_new_stack(ft_simple_quotes(input, &i)));
        else if (input[i] == ' ')
            i++;
        else
        {
            if (input[i] != '$')
            {
                while (input[j] && input[j] != ' ')
                    j++;
                addlast_node(&data, ft_new_stack(ft_substr(input, i, j - i)));
                i = j + 1;
            }
            else
            {
                res = ft_dollar_sign(input, &i, envp);
                if (res)
                    addlast_node(&data, ft_new_stack(ft_dollar_sign(input, &i, envp)));
            }
        }
    }
    return (data);
}
