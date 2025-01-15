/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pboucher <pboucher@42student.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/11 15:23:35 by pboucher          #+#    #+#             */
/*   Updated: 2025/01/15 17:05:08 by pboucher         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


void handler(int n)
{
	// printf("\n%d\n", n);
	if (n == SIGINT)
		ft_printf("\n• minishell } ");
	if (n == SIGQUIT)
		return ;
}

int ft_strcmp(char *s1, char *s2)
{
	int i;
	int j;

	i = 0;
	while (s1[i])
	{
		j = 0;
		if (s1[i] == s2[j])
		{
			while (s2[j] && s1[i] == s2[j])
			{
				j++;
				i++;
			}
			if (!s2[j])
				return (1);
		}
		i++;
	}
	return (0);
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
		if (ft_strcmp(data.line, "exit") || !data.line)
			break ;
		data.input = ft_pipe_split(data.line);
		ft_printf("%*.2[\n]s\n", data.input);
		ft_free_slines(&data.input);
		free(data.line);
		data.line = NULL;
	}
	ft_free_rlines(&data.envp);
	ft_printf("exit\n");
	return (0);
}
