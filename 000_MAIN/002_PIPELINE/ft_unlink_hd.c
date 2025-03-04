/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unlink_hd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzhen-cl <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 14:30:08 by kzhen-cl          #+#    #+#             */
/*   Updated: 2025/03/03 14:42:47 by kzhen-cl         ###   ########.fr       */
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
		hd_name = gnlxio_ft_strjoinfree(&(char *){ft_strdup(".minipk_hd")},
				&(char *){ft_itoa(i)});
		if (!hd_name)
		{
			ft_printf_err("Internal Error:gnlxio_ft_strjoinfree()", 2);
			return ;
		}
		unlink(hd_name);
		free(hd_name);
	}
}
