/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_redirec.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzhen-cl <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 10:40:22 by kzhen-cl          #+#    #+#             */
/*   Updated: 2025/01/25 10:40:23 by kzhen-cl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	finish_symbols(char *part)
{
	return (!ft_strncmp(part, ">>", -1)
		|| !ft_strncmp(part, "<<", -1)
		|| !ft_strncmp(part, ">", -1)
		|| !ft_strncmp(part, "<", -1));
}

static int	free_return(const char *msg, char *buffer1, char *buffer2)
{
	free(buffer1);
	free(buffer2);
	ft_printf_err(msg, 2);
	return (-1);
}

static int	rewrite(t_rlines *part, int j, int x)
{
	char	*pop;
	char	*add;
	char	*rewrite;

	pop = ft_rlines_pop(part, j);
	if (!pop)
		return (ft_printf_err("Internal Error:ft_rlines_pop(%*.)", 2));
	add = ft_substr(pop, x, -1);
	if (!add)
		return (free_return("Internal Error:ft_substr()", pop, NULL));
	if (ft_rlines_add(part, add, j) == -1)
		return (free_return("Internal Error:ft_rlines_add()", add, pop));
	rewrite = ft_substr(pop, 0, x);
	if (!rewrite)
		return (free_return("Internal Error:ft_substr()", pop, NULL));
	if (ft_rlines_add(part, rewrite, j) == -1)
		return (free_return("Internal Error:ft_substr()", rewrite, pop));
	free(pop);
	return (0);
}

static int	is_valid_symbol(char *str, int x)
{
	return ((x > 0 && str[x - 1] != '>' && str[x - 1] != '<')
		&& (str[x] == '>' || str[x] == '<'));
}

int	ft_split_redirec(t_rlines *part, int j)
{
	t_ints	i;

	i.x = -1;
	i.count1 = 0;
	i.count2 = 0;
	while ((*part)[j][++(i.x)])
	{
		if (!i.count2 && (*part)[j][i.x] == '\'')
			i.count1 = !i.count1;
		else if (!i.count1 && (*part)[j][i.x] == '"')
			i.count2 = !i.count2;
		if (i.count1 + i.count2)
			continue ;
		if (is_valid_symbol((*part)[j], i.x)
			&& !finish_symbols((*part)[j] + i.x))
			return (rewrite(part, j, i.x));
	}
	return (0);
}
