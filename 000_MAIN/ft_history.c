/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_history.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pboucher <pboucher@42student.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 16:03:54 by pboucher          #+#    #+#             */
/*   Updated: 2025/02/28 18:31:29 by pboucher         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	*ft_get_abspath(void)
{
	char	*temp;

	temp = ft_pick_env("HOME");
	temp = gnlxio_ft_strjoinfree(&temp,
			&(char *){ft_strdup("/.minipk_history")});
	return (temp);
}

void	ft_gen_history(t_data *data)
{
	t_rlines	hist;
	int			i;

	data->history = ft_get_abspath();
	if (ft_gen_file(data->history, "0777") == -1)
	{
		ft_printf_fd(ERROR_CCH, 2);
		return ;
	}
	hist = ft_readfile(data->history);
	if (!hist)
	{
		ft_printf_err("Internal Error:ft_readfile()", 2);
		return ;
	}
	if (zombie_rlines_free(&hist))
		return ;
	ft_rlines_cutendl(&hist);
	i = -1;
	while (hist[++i])
		add_history(hist[i]);
	ft_free_rlines(&hist);
}

void	ft_add_history(t_data *data)
{
	char	*temp;

	if (!data->line[0])
		return ;
	temp = ft_get_line(data->history, A_END);
	if (!temp && access(data->history, W_OK | R_OK))
	{
		add_history(data->line);
		return ;
	}
	ft_rline_cutendl(&temp);
	if (!temp || ft_strncmp(temp, data->line, -1))
	{
		add_history(data->line);
		ft_add_line(data->history, data->line, A_END);
	}
	free(temp);
}
