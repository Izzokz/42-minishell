/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_signals.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pboucher <pboucher@42student.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 12:01:03 by pboucher          #+#    #+#             */
/*   Updated: 2025/03/15 12:50:31 by pboucher         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	sig_restore(void)
{
	signal(SIGQUIT, SIG_DFL);
	signal(SIGINT, SIG_DFL);
}

void	handler(int n)
{
	t_data	*data;

	if (n == SIGINT)
	{
		data = ft_get_tdata();
		data->err_num = 130;
		ft_printf("\n");
		if (!data->pipeline)
		{
			rl_on_new_line();
			rl_replace_line("", 0);
			rl_redisplay();
		}
	}
}

void	check_signal(t_data *data, t_ints *signal)
{
	data->err_num = WTERMSIG(signal->tmp1);
	if (data->err_num == 2)
		data->err_num = 130;
	else if (data->err_num == 3 && (signal->tmp2 == -127))
	{
		signal->tmp2 = 131;
		data->err_num = 131;
		ft_printf("Quit\n");
	}
	else if (data->err_num == 13)
		data->err_num = 0;
}

int	find_err_num(t_data *data, t_ints *i)
{
	while (waitpid(-1, &i->tmp1, 0) > 0)
	{
		if (WIFEXITED(i->tmp1))
			i->tmp2 = WEXITSTATUS(i->tmp1);
		if (WIFSIGNALED(i->tmp1))
			check_signal(data, i);
	}
	data->err_num = i->tmp2;
	return (0);
}
