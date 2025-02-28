/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pboucher <pboucher@42student.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 17:30:08 by pboucher          #+#    #+#             */
/*   Updated: 2025/02/28 19:23:50 by pboucher         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	ft_check_export(t_data *data, t_rlines cmd, t_ints *ints)
{
	char	*str;

	str = ft_substr(cmd[ints->i], 0, ft_strlen(cmd[ints->i]) - 1);
	ints->j = -1;
	while (data->var[++ints->j])
	{
		if (!ft_strncmp(data->var[ints->j], str, ft_strlen(str))
			&& (ft_strlen(str) == ft_strlen(data->var[ints->j])))
		{
			ft_rlines_delete(&data->var, ints->j);
			break ;
		}
	}
	free(str);
}

static void	ft_remove_unset(t_data *data, t_rlines cmd, t_ints *ints)
{
	cmd[ints->i] = gnlxio_ft_strjoinfree(&cmd[ints->i],
			&(char *){ft_strdup("=")});
	ints->j = -1;
	while (data->envp[++ints->j])
	{
		if (!ft_strncmp(data->envp[ints->j],
				cmd[ints->i], ft_strlen(cmd[ints->i])))
		{
			ft_rlines_delete(&data->envp, ints->j);
			break ;
		}
	}
	if (!data->envp[ints->j])
		ft_check_export(data, cmd, ints);
	ints->j = -1;
	while (data->var[++ints->j])
	{
		if (!ft_strncmp(data->var[ints->j],
				cmd[ints->i], ft_strlen(cmd[ints->i])))
		{
			ft_rlines_delete(&data->var, ints->j);
			break ;
		}
	}
}

int	ft_unset(t_data *data, t_rlines cmd)
{
	t_ints	ints;

	ints.len = ft_rlines_len(cmd);
	if (ints.len == 1)
		return (ft_printf_fd(ERROR_NEA, 2) + 1);
	ints.i = 0;
	while (cmd[++ints.i])
	{
		if (!ft_strncmp(cmd[ints.i], "PATH", -1))
			ft_free_rlines(&(data->path));
		ft_remove_unset(data, cmd, &ints);
	}
	return (0);
}
