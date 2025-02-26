/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pboucher <pboucher@42student.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 13:52:47 by pboucher          #+#    #+#             */
/*   Updated: 2025/02/26 17:41:03 by pboucher         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	ft_print_var(t_rlines var)
{
	t_ints	num;

	num.i = -1;
	while (var[++(num.i)])
	{
		num = (t_ints){.i = num.i, .j = -1, .tmp = 0};
		ft_printf("declare -x ");
		while (var[num.i][++(num.j)])
		{
			ft_printf("%c", var[num.i][num.j]);
			if (var[num.i][num.j] == '=')
			{
				num.tmp = 1;
				ft_printf("\"");
				break ;
			}
		}
		if (num.tmp)
			ft_printf("%s\"\n", var[num.i] + num.j + 1);
		else
			ft_printf("\n");
	}
}

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
