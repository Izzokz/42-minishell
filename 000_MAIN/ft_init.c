/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pboucher <pboucher@42student.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 12:59:14 by pboucher          #+#    #+#             */
/*   Updated: 2025/03/16 12:32:01 by pboucher         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_init(int ac, char **av, char **envp, t_data *data)
{
	(void) ac;
	(void) av;
	ft_set_tdata(data);
	if (set_data(data, envp) == -1)
		return (-1);
	up_shlvl(data);
	ft_gen_history(data);
	signal(SIGINT, handler);
	signal(SIGQUIT, SIG_IGN);
	return (0);
}

int	ft_init_history(t_data *data)
{
	data->last_history = NULL;
	data->temp_history = ft_calloc(1, sizeof(char *));
	if (!data->temp_history)
	{
		ft_printf_err(ERROR_IE"ft_calloc(%*.)", 2);
		return (0);
	}
	data->history = ft_get_abspath();
	if (ft_gen_file(data->history, "0777") == -1)
	{
		ft_printf_fd(ERROR_CCH, 2);
		return (0);
	}
	return (1);
}

void	init_loop(t_data *data, t_ints *i)
{
	i->len = ft_pipeline_tab_len(data->pipeline);
	i->i = -1;
	i->tmp2 = -127;
}
