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

static int	do_hd(t_data *data, t_pipeline **prev, t_pipeline **pl, char *did_hd)
{
	t_pipeline	*tmp;

	tmp = (*pl)->next;
	if ((*pl)->func == ft_here_doc)
	{
		*did_hd = 1;
		if ((*pl)->func(data, (*pl)->param) == -1)
			return (-1);
		(*pl)->free((*pl)->param);
		free(*pl);
		if (*prev)
			(*prev)->next = tmp;
	}
	*pl = tmp;
	return (0);
}

static int	ft_pre_hd(t_data *data, t_pipeline *pl)
{
	char		did_hd;
	t_pipeline	*prev;
	char		*hd_name;

	did_hd = 0;
	prev = NULL;
	while (pl)
	{
		if (pl->func == ft_here_doc && do_hd(data, &prev, &pl, &did_hd) == -1)
			return (-1);
		if (pl != prev)
			prev = pl;
		pl = pl->next;
	}
	if (!did_hd || prev->func != ft_here_doc)
		return (1);
	data->pipeline[data->hd_i] = pl;
	hd_name = gnlxio_ft_strjoinfree(&(char *){ft_strdup(".minipk_hd")},
			&(char *){ft_itoa(data->hd_i)});
	if (!hd_name || !ft_add_front_pipeline(&(data->pipeline[data->hd_i]),
			ft_open_read, hd_name, free))
		return (-1);
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
