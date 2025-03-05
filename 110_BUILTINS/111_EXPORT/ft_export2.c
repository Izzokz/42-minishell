/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pboucher <pboucher@42student.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 13:52:47 by pboucher          #+#    #+#             */
/*   Updated: 2025/03/05 15:22:03 by pboucher         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
    {
        free(dup);
        free(data->var[ints->k]);
        data->var[ints->k] = ft_strdup(cmd[ints->i]);
    }
    else
    {
        free(dup);
        dup = ft_strdup(cmd[ints->i]);
        ft_rlines_add(&(data->var), dup, A_END);
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
    {
        free(dup);
        free(data->envp[ints->k]);
        data->envp[ints->k] = ft_strdup(cmd[ints->i]);
    }
    else
    {
        free(dup);
        dup = ft_strdup(cmd[ints->i]);
        ft_rlines_add(&(data->envp), dup, A_END);
    }
}
