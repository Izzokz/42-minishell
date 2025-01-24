/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pboucher <pboucher@42student.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/11 15:23:35 by pboucher          #+#    #+#             */
/*   Updated: 2025/01/24 15:51:51 by pboucher         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void handler(int n)
{
	if (n == SIGINT)
	{
		ft_printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

static void ft_loop(t_data *data)
{
	t_ints	i;

	i.i = -1;
	while (data->input[++(i.i)])
	{
		i.j = -1;
		while (data->input[i.i][++(i.j)])
		{
			data->exe = 1;
			ft_exec(data, *(data)->input);
			// ft_free_all(data);
			// exit(127);
		}
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_data data;

	(void) argc;
	(void) argv;
	data.envp = ft_rlines_dup(envp);
	if (!data.envp)
		return (ft_printf_err("Internal Error:ft_rlines_dup(%*.)", 2));
	ft_set_path(&data);
	if (!data.path)
		return (ft_printf_err("Internal Error:ft_set_path(%*.)", 2));
	while (1)
	{
		signal(SIGINT, handler);
		signal(SIGQUIT, SIG_IGN);
		data.line = readline("\e[1;33m]>Minishell » \e[0;97m");
		ft_printf("\e[0m");
		if (!data.line)
			break ;
		if (!!data.line[0])
		{
			data.input = ft_pipe_split(data.line);
			//data.pipeline = ft_make_pipeline(&data);
			//ft_printf("%*.2[\n]s\n", data.input); //just testing the parsing.
			ft_loop(&data); // does not work yet so there's a return in the first line of the funct
			while (wait(NULL) > 0)
				;
			if (!data.line) // if exit in the pipeline, frees input and returns instantly.
				break ;
			ft_free_slines(&data.input);
		}
		free(data.line);
		data.line = NULL;
	}
	ft_free_all(&data);
	//system("clear");
	ft_printf("exit\n");
	return (0);
}
