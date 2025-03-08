/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_valid_input.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pboucher <pboucher@42student.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 17:46:31 by kzhen-cl          #+#    #+#             */
/*   Updated: 2025/03/08 10:03:12 by pboucher         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	end_cases(char count[3])
{
	if (count[0])
		return (ft_printf_fd("ERROR_END_<%*.\n", 2) + 1);
	if (count[1])
		return (ft_printf_fd("ERROR_END_>%*.\n", 2) + 1);
	if (count[2])
		return (ft_printf_fd("ERROR_END_|%*.\n", 2) + 1);
	return (1);
}

/*
Makes this kind of case work : ls |>>out cat
*/
static void	add_redirec(char *red, char *pipe)
{
	(*red)++;
	*pipe = 0;
}

/*
"cnt" stands for count. Each index counts the number of following :
- cnt[0] '<';
- cnt[1] '>';
- cnt[2] '|';
<cnt> is often reset so this works : ls >> out | ls -l >> out1
*/
static int	pipe_redirec_cases(char actual, t_ints i)
{
	static char	cnt[3] = {0, 0, 0};

	if (!actual)
		return (end_cases(cnt));
	if (ft_strchr(" \t\n\v\f\r", actual))
		return (1);
	if (i.count1 || i.count2)
		ft_bzero(cnt, 3);
	else if (actual == '|')
		cnt[2]++;
	else if (actual == '<')
		add_redirec(&(cnt[0]), &(cnt[2]));
	else if (actual == '>')
		add_redirec(&(cnt[1]), &(cnt[2]));
	else
		ft_bzero(cnt, 3);
	if (cnt[0] > 2)
		return (ft_printf_fd(ERROR_TMA"<%*.\n", 2) + 1);
	if (cnt[1] > 2)
		return (ft_printf_fd(ERROR_TMA">%*.\n", 2) + 1);
	if (cnt[2] > 1)
		return (ft_printf_fd(ERROR_TMA"|%*.\n", 2) + 1);
	if ((cnt[0] && cnt[1]) || (cnt[0] && cnt[2]) || (cnt[1] && cnt[2]))
		return (ft_printf_fd(ERROR_US"%*.\n", 2) + 1);
	return (1);
}

/*
i.count1 determines if a single quote is opened
i.count2 determines if a double quote is opened
*/
int	ft_valid_input(char *input)
{
	t_ints	i;

	i.count1 = 0;
	i.count2 = 0;
	i.i = -1;
	while (input[++i.i])
	{
		if (!i.count1 && ((input[i.i] == '\\' && input[i.i + 1] == '"')
				|| (input[i.i] == '\\' && input[i.i + 1] == '\\')))
			i.i++;
		else if (!i.count2 && input[i.i] == '\'')
			i.count1 = !i.count1;
		else if (!i.count1 && input[i.i] == '"')
			i.count2 = !i.count2;
		if (!pipe_redirec_cases(input[i.i], i))
			return (0);
	}
	if (!pipe_redirec_cases(0, i))
		return (0);
	if (i.count1 + i.count2)
		return (ft_printf_fd(ERROR_UQ, 2) + 1);
	return (1);
}
