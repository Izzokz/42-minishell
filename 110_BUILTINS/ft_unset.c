/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pboucher <pboucher@42student.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 17:30:08 by pboucher          #+#    #+#             */
/*   Updated: 2025/01/29 18:46:15 by pboucher         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_unset(t_data *data, t_rlines cmd)
{
	t_ints	ints;

	ints.len = ft_rlines_len(cmd);
	if (ints.len == 1)
		return (ft_printf_fd("\e[1;31m[Minishell] \e[0;97m%s\e[0m\n%*.", 2,
				"not enough arguments") + 1);
	ints.i = 0;
	while (cmd[++ints.i])
	{
		cmd[ints.i] = gnlxio_ft_strjoinfree(&cmd[ints.i],
				&(char *){ft_strdup("=")});
		ints.j = -1;
		while (data->envp[++ints.j])
		{
			if (!ft_strncmp(data->envp[ints.j],
					cmd[ints.i], ft_strlen(cmd[ints.i])))
			{
				ft_rlines_delete(&data->envp, ints.j);
				break ;
			}
		}
	}
	return (0);
}
