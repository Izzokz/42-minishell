/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_history.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pboucher <pboucher@42student.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 16:03:54 by pboucher          #+#    #+#             */
/*   Updated: 2025/02/11 16:32:48 by pboucher         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	*ft_get_abspath(void)
{
	char	*temp;

	temp = ft_strdup(getenv("HOME"));
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
   		ft_printf_err("Internal Error:ft_gen_file()", 2);
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
}

void	ft_add_history(t_data *data)
{
	char *temp;

	add_history(data->line);
	temp = ft_get_line(data->history, A_END);
	if (!temp)
	{
		ft_printf_err("Internal Error:ft_get_line()", 2);
		return ;
	}
	ft_rline_cutendl(&temp);
	if (ft_strncmp(temp, data->line, -1))
		ft_add_line(data->history, data->line, A_END);
	free(temp);
}