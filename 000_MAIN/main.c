/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pboucher <pboucher@42student.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/11 15:23:35 by pboucher          #+#    #+#             */
/*   Updated: 2025/03/13 15:51:20 by pboucher         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	handler(int n)
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

static int	ft_init(int ac, char **av, char **envp, t_data *data)
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

void	ft_get_user(t_data *data)
{
	t_ints	num;

	num.i = -1;
	while (data->envp && data->envp[++(num.i)])
		if (!ft_strncmp(data->envp[num.i], "USER=", 5))
			break ;
	if (!data->envp || !data->envp[num.i])
		data->user = ft_strdup("user");
	else
		data->user = ft_substr(data->envp[num.i], 5, -1);
}

static int	finish(t_data *data)
{
	ft_add_all_history(data);
	ft_exit(data, NULL);
	return (0);
}

int	main(int argc, char **argv, char **envp)
{
	t_data	data;

	if (ft_init(argc, argv, envp, &data) == -1)
		return (-1);
	while (1)
	{
		ft_show_prompt(&data);
		if (!data.line)
			break ;
		ft_add_history(&data);
		if (!ft_valid_input(data.line) && ft_free_line(&data))
			continue ;
		if (data.line[0])
		{
			data.input = ft_pipe_split(data.line);
			ft_free_line(&data);
			if (!data.input || ft_make_pipeline(&data) == -1)
				break ;
			ft_hd_loop(&data);
			ft_destroy_all_pipelines(&(data.pipeline));
			ft_free_slines(&data.input);
		}
		ft_free_line(&data);
	}
	return (finish(&data));
}
