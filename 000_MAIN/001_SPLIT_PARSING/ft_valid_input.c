/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_valid_input.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzhen-cl <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 17:46:31 by kzhen-cl          #+#    #+#             */
/*   Updated: 2025/02/10 17:46:32 by kzhen-cl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	}
	if (i.count1 + i.count2)
	{
		free(input);
		return (ft_printf_fd("\e[1;31m[Minishell] \e[0;97m%s\e[0m\n%*.",
				2, "Unfinished quotes") + 1);
	}
	return (1);
}
