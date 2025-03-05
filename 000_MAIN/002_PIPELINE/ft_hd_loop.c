/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hd_loop.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzhen-cl <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 11:37:16 by kzhen-cl          #+#    #+#             */
/*   Updated: 2025/03/03 11:37:17 by kzhen-cl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	change_vars(t_data *data, t_pipeline *pl_datas)
{
	char	*hd_name;

	hd_name = gnlxio_ft_strjoinfree(&(char *){ft_strdup("..!minipk_hd")},
			&(char *){ft_itoa(data->hd_i)});
	if (!hd_name)
		return (-1);
	pl_datas->func = ft_open_read;
	pl_datas->free(pl_datas->param);
	pl_datas->param = hd_name;
	return (0);
}

static int	do_hd(t_data *data, t_pipeline **pl)
{
	if ((*pl)->func == ft_here_doc)
	{
		if ((*pl)->func(data, (*pl)->param) == -1)
			return (-1);
		if (change_vars(data, *pl) == -1)
			return (-1);
	}
	return (0);
}

static int	ft_pre_hd(t_data *data, t_pipeline *pl)
{
	while (pl)
	{
		if (pl->func == ft_here_doc && do_hd(data, &pl) == -1)
			return (-1);
		pl = pl->next;
	}
	return (1);
}

int	ft_hd_loop(t_data *data)
{
	int	ret;

	data->hd_i = -1;
	while (data->pipeline[++(data->hd_i)])
		if (ft_pre_hd(data, data->pipeline[data->hd_i]) == -1)
			return (-1);
	ret = ft_loop(data);
	ft_unlink_hd(data);
	return (ret);
}
