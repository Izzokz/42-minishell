/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pboucher <pboucher@42student.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 18:22:15 by pboucher          #+#    #+#             */
/*   Updated: 2025/03/08 11:29:56 by pboucher         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static bool ft_valid(char *cmd)
{
    int i;

    if (!cmd)
        return (false);
    if (cmd[0] != '-')
        return (false);
    i = 0;
    while (cmd[++i])
        if (cmd[i] != 'n')
            return (false);
    return (true);
}

int	ft_echo(t_rlines cmd)
{
    t_ints	ints;

    ints.count = 0;
    ints.len = ft_rlines_len(cmd);
    if (ints.len == 1)
        return (ft_printf("\n"));
    ints.i = 1;
    while (ft_valid(cmd[ints.i]))
        ints.i++;
    ft_printf("%*[ ]s", cmd + ints.i);
    if (ints.i == 1)
        ft_printf("\n");
    return (0);
}
