/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pboucher <pboucher@42student.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/11 15:23:35 by pboucher          #+#    #+#             */
/*   Updated: 2025/01/15 17:46:34 by pboucher         ###   ########.fr       */
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
		ft_printf("\n• minishell } ");
	if (n == SIGQUIT)
		return ;
}

int	main(int argc, char **argv, char **envp)
{
	t_data data;

	(void) argc;
	(void) argv;
	data.envp = ft_rlines_dup(envp);
	while (1)
	{
		signal(SIGINT, handler);
		signal(SIGQUIT, handler);
		data.line = readline("• minishell } ");
		if (!data.line)
			break ;
		data.input = ft_pipe_split(data.line);
		ft_printf("%*.2[\n]s\n", data.input); //just testing the parsing.
		//ft_exit(data.input);
		//replace ft_exit() by the executor function.
		if (!data.line) // if exit in the pipeline, frees input and returns instantly.
			break ;
		ft_free_slines(&data.input);
		free(data.line);
		data.line = NULL;
	}
	ft_free_all(&data);
	ft_printf("exit\n");
	return (0);
}
