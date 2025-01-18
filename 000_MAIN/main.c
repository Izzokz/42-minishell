/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pboucher <pboucher@42student.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/11 15:23:35 by pboucher          #+#    #+#             */
/*   Updated: 2025/01/18 16:39:17 by pboucher         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
/*
void	ft_exit(t_rlines command)
{
	if (command[0] == "exit")
		exit(0);
}
*/
void handler(int n)
{
	// printf("\n%d\n", n);
	if (n == SIGINT)
	{
		ft_printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	if (n == SIGQUIT)
		return ;
}

int ft_strcmp(char *s1, char *s2)
{
	int	i;
	
	i = 0;
	while (s1[i] && s2[i] && s1[i] == s2[i])
		i++;
	return (s2[i] - s1[i]);
}

void ft_loop(t_data *data)
{
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

	data.exit = 0;
	(void) argc;
	(void) argv;
	data.envp = ft_rlines_dup(envp);
	while (1)
	{
		signal(SIGINT, handler);
		signal(SIGQUIT, handler);
		data.line = readline("\e[92m• minishell (} \e[97m");
		if (!data.line )
			break ;
		data.input = ft_pipe_split(data.line);
		ft_printf("%*.2[\n]s\n", data.input); //just testing the parsing.
		//ft_exit(data.input);
		ft_loop(&data);
		if (!data.line || data.exit) // if exit in the pipeline, frees input and returns instantly.
			break ;
		ft_free_slines(&data.input);
		free(data.line);
		data.line = NULL;
	}
	ft_free_all(&data);
	ft_printf("exit\n");
	return (0);
}
