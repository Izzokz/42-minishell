/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_history.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pboucher <pboucher@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 16:03:54 by pboucher          #+#    #+#             */
/*   Updated: 2025/03/15 21:25:40 by pboucher         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_get_abspath(void)
{
	char	*temp;

	temp = ft_pick_env("HOME");
	temp = gnlxio_ft_strjoinfree(&temp,
			&(char *){ft_strdup("/.minipk_history")});
	return (temp);
}

void	ft_gen_history(t_data *data)
{
	int			i;
	t_rlines	hist;

	if (!ft_init_history(data))
		return ;
	hist = ft_readfile(data->history);
	if (!hist)
	{
		ft_printf_err(ERROR_IE"ft_readfile(%*.)", 2);
		return ;
	}
	if (zombie_rlines_free(&hist))
		return ;
	ft_rlines_cutendl(&hist);
	i = -1;
	while (hist[++i])
		add_history(hist[i]);
	if (i - 1 > 0)
		data->last_history = ft_strdup(hist[i - 1]);
	ft_free_rlines(&hist);
}

void	ft_add_history(t_data *data)
{
	if (!data->line[0])
		return ;
	ft_rline_cutendl(&data->last_history);
	if (!data->last_history || ft_strncmp(data->last_history, data->line, -1))
	{
		add_history(data->line);
		ft_rlines_add(&data->temp_history, (char *){ft_strdup(data->line)},
			A_END);
		if (data->last_history)
			free(data->last_history);
		data->last_history = ft_strdup(data->line);
	}
}

void	ft_add_all_history(t_data *data)
{
	int	i;

	i = -1;
	while (data->temp_history[++i])
		ft_add_line(data->history, data->temp_history[i], A_END);
}
