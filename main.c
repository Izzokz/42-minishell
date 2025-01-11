/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pboucher <pboucher@42student.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/11 15:23:35 by pboucher          #+#    #+#             */
/*   Updated: 2025/01/11 16:29:17 by pboucher         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_prompt(char *prompt)
{
	ft_printf("%s > ", prompt);
	return (ft_input());	
}

void	handle_signal(int signal, siginfo_t *signals, void *context)
{
	(void)context;
	(void)signals;
	if (signal == SIGINT)
		ft_printf("test");
}

int	main(int argc, char **argv, char **envp)
{
	t_data data;

	(void) argc;
	(void) argv;
	sigaction(SIGINT, &data.usr, NULL);
	data.usr.sa_sigaction = handle_signal;
	data.envp = ft_rlines_dup(envp);
	data.line = readline("minishell");
	while (data.line)
	{
		free(data.line);
		data.line = readline("minishell");
		printf("Line you wrote: %s\n", data.line);
		if (data.line[0] == '\0')
		{
			free(data.line);
			data.line = NULL;
		}
	}
	ft_free_rlines(&data.envp);
	return (0);
}