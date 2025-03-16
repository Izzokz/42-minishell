/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pboucher <pboucher@42student.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 17:30:08 by pboucher          #+#    #+#             */
/*   Updated: 2025/03/16 12:37:25 by pboucher         ###   ########.fr       */
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
		ft_rlines_add(&(data->var), (char *){ft_strdup(cmd[ints->i])}, A_END);
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
		ft_rlines_add(&(data->envp), (char *){ft_strdup(cmd[ints->i])}, A_END);
	}
}

static int	ft_execute(t_data *data, t_rlines cmd, t_ints *ints)
{
	char	*dup;

	if (ints->j > 0)
	{
		dup = ft_substr(cmd[ints->i], 0, ints->j + 1);
		if (!dup)
			return (ft_printf_err(ERROR_IE"ft_substr(%*.)", 2));
		ft_make_export(data, cmd, ints, dup);
		dup = ft_substr(cmd[ints->i], 0, ints->j);
		if (!dup)
			return (ft_printf_err(ERROR_IE"ft_substr(%*.)", 2));
		ft_make_var(data, cmd, ints, dup);
	}
	else if (ints->j == 0)
	{
		dup = ft_substr(cmd[ints->i], 0, -1);
		if (!dup)
			return (ft_printf_err(ERROR_IE"ft_substr(%*.)", 2));
		ft_make_var(data, cmd, ints, dup);
	}
	else
		data->err_num = (ft_printf_fd(ERROR_NVI, 2) + 2);
	return (0);
}

int	ft_export(t_data *data, t_rlines cmd)
{
	t_ints	ints;

	data->err_num = 0;
	ints.len = ft_rlines_len(cmd);
	if (ints.len == 1)
		return (ft_print_export(data));
	ints.i = 0;
	while (cmd[++(ints.i)])
	{
		ints.j = ft_chr(cmd[ints.i]);
		ft_execute(data, cmd, &ints);
	}
	return (0);
}
