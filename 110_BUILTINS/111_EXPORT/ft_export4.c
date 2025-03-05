/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export4.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pboucher <pboucher@42student.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 13:52:47 by pboucher          #+#    #+#             */
/*   Updated: 2025/02/26 17:41:03 by pboucher         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_print_export(t_data *data)
{
    char		*max;
    t_ints		num;
    t_rlines	var;

    var = ft_rlines_dup(data->var);
    num.len = ft_rlines_len(var);
    while (--num.len >= 0)
    {
        max = "\0";
        num = (t_ints){.count = num.len + 1, .j = num.len, .len = num.len};
        while (--num.count >= 0)
        {
            if (is_greater(var[num.count], max))
            {
                max = var[num.count];
                num.i = num.count;
            }
        }
        max = var[num.i];
        var[num.i] = var[num.j];
        var[num.j] = max;
    }
    ft_print_var(var);
    ft_free_rlines(&var);
    return (0);
}

int	is_greater(char *s1, char *s2)
{
    int	index;

    index = 0;
    while (s1[index] && s1[index] == s2[index])
        index++;
    if (s1[index] > s2[index])
        return (1);
    return (0);
}
