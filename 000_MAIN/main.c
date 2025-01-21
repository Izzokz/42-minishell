/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pboucher <pboucher@42student.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/11 15:23:35 by pboucher          #+#    #+#             */
/*   Updated: 2025/01/21 17:03:24 by pboucher         ###   ########.fr       */
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

// static int ft_strcmp(char *s1, char *s2)
// {
// 	int	i;

// 	i = 0;
// 	while (s1[i] && s2[i] && s1[i] == s2[i])
// 		i++;
// 	return (s2[i] - s1[i]);
// }

static void ft_loop(t_data *data)
{
	return ;
	t_ints	i;

	i.i = -1;
	while (data->pipeline[++(i.i)])
	{
		i.j = -1;
		while (data->pipeline[i.i][++(i.j)])
		{
			if (data->pipeline[i.i][i.j][0] == 'e')
				ft_printf("%s\n", data->pipeline[i.i][i.j]);
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
	while (1)
	{
		signal(SIGINT, handler);
		signal(SIGQUIT, SIG_IGN);
		data.line = readline("\e[33mMinishell ⮞⮞ \e[97m");
		if (!data.line )
			break ;
		data.input = ft_pipe_split(data.line);
		//data.pipeline = ft_make_pipeline(&data);
		//ft_printf("%*.2[\n]s\n", data.input); //just testing the parsing.
		ft_loop(&data); // does not work yet so there's a return in the first line of the funct
		if (!data.line) // if exit in the pipeline, frees input and returns instantly.
			break ;
		ft_free_slines(&data.input);
		free(data.line);
		data.line = NULL;
	}
	ft_free_all(&data);
	// system("clear");
	ft_printf("exit\n");
	return (0);
}
