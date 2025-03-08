/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unlink_hd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pboucher <pboucher@42student.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 14:30:08 by kzhen-cl          #+#    #+#             */
/*   Updated: 2025/03/08 10:04:37 by pboucher         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_unlink_hd(t_data *data)
{
	char	*hd_name;
	int		i;

	i = -1;
	while (data->pipeline[++i])
	{
		hd_name = gnlxio_ft_strjoinfree(&(char *){ft_strdup("..!minipk_hd")},
				&(char *){ft_itoa(i)});
		if (!hd_name)
		{
			ft_printf_err(ERROR_IE"gnlxio_ft_strjoinfree()", 2);
			return ;
		}
		unlink(hd_name);
		free(hd_name);
	}
}
