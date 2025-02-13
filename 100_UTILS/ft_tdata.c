/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tdata.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzhen-cl <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 16:38:29 by kzhen-cl          #+#    #+#             */
/*   Updated: 2025/02/11 16:38:29 by kzhen-cl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_data	*ft_tdata(t_data *info)
{
	static t_data	*data = NULL;

	if (info)
		data = info;
	return (data);
}

void	ft_set_tdata(t_data *info)
{
	ft_tdata(info);
}

t_data	*ft_get_tdata(void)
{
	return (ft_tdata(NULL));
}
