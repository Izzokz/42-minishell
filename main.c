/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pboucher <pboucher@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/11 15:23:35 by pboucher          #+#    #+#             */
/*   Updated: 2025/01/13 16:48:00 by pboucher         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_signal(int signal, siginfo_t *signals, void *context)
{
	t_data	*data;

	data = (t_data *)context;
	(void) signals;
	if (signal == SIGINT)
	{
		ft_printf("\ntest: reprompt");
	}
	if (signal == SIGQUIT)
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
		data.usr.sa_sigaction = handle_signal;
		sigaction(SIGINT, &data.usr, NULL);
		sigaction(SIGQUIT, &data.usr, NULL);
		data.line = readline("• minishell } ");
		if (!data.line || data.line[0] == '\0')
		{
			free(data.line);
			data.line = NULL;
			break ;
		}
		free(data.line);
		data.line = NULL;
	}
	ft_free_rlines(&data.envp);
	return (0);
}
