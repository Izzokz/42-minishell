/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pboucher <pboucher@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 13:52:47 by pboucher          #+#    #+#             */
/*   Updated: 2025/03/05 00:56:40 by pboucher         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	update_var(t_data *data, t_rlines cmd, t_ints *ints, char *dup)
{
	char *new_value;

    free(dup);
    if (cmd[ints->i][ints->j - 1] == '+')
    {
        new_value = ft_strjoin(data->var[ints->k], cmd[ints->i] + ints->j + 1);
        free(data->var[ints->k]);
        data->var[ints->k] = new_value;
    }
    else
    {
        free(data->var[ints->k]);
        data->var[ints->k] = ft_strdup(cmd[ints->i]);
    }
}

void	ft_make_var(t_data *data, t_rlines cmd, t_ints *ints, char *dup)
{
    ints->k = -1;
    ints->count = 0;
    if (ints->j == 0 && ft_is_env(dup))
        return ;
    while (data->var[++ints->k])
    {
        ints->count1 = ft_strncmp(data->var[ints->k], dup, ft_strlen(dup));
        if (!ints->count1)
        {
            ints->count++;
            break ;
        }
    }
    if (ints->count)
        update_var(data, cmd, ints, dup);
    else
    {
        free(dup);
        dup = ft_strdup(cmd[ints->i]);
        ft_rlines_add(&(data->var), dup, A_END);
    }
}

static void	update_export(t_data *data, t_rlines cmd, t_ints *ints, char *dup)
{
	char *new_value;

    free(dup);
    if (cmd[ints->i][ints->j - 1] == '+')
    {
    	new_value = ft_strjoin(data->envp[ints->k], cmd[ints->i] + ints->j + 1);
        free(data->envp[ints->k]);
        data->envp[ints->k] = new_value;
    }
    else
    {
        free(data->envp[ints->k]);
        data->envp[ints->k] = ft_strdup(cmd[ints->i]);
    }
}

void	ft_make_export(t_data *data, t_rlines cmd, t_ints *ints, char *dup)
{
    ints->k = -1;
    ints->count = 0;
    while (data->envp[++ints->k])
    {
        ints->count1 = ft_strncmp(data->envp[ints->k], dup, ft_strlen(dup));
        if (!ints->count1)
        {
            ints->count++;
            break ;
        }
    }
    if (ints->count)
        update_export(data, cmd, ints, dup);
    else
    {
        free(dup);
        dup = ft_strdup(cmd[ints->i]);
        ft_rlines_add(&(data->envp), dup, A_END);
    }
}
