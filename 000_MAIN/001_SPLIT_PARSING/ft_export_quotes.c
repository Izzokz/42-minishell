/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_quotes.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzhen-cl <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 15:19:03 by kzhen-cl          #+#    #+#             */
/*   Updated: 2025/03/10 15:19:04 by kzhen-cl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	get_assign_index(char *set)
{
	int	i;

	i = -1;
	while (*(set + ++i))
		if (*(set + i) == '=')
			return (i);
	return (-1);
}

static char	is_quote(char c)
{
	return (c == '\'' || c == '"');
}

static int	handle_ecase(t_slines *input, t_ints i)
{
	char	*varname;
	char	*new_str;
	int		index;

	while (*(*((*input) + i.i) + ++i.j))
	{
		index = get_assign_index(*(*((*input) + i.i) + i.j));
		if (index < 0 || !is_quote(*(*(*((*input) + i.i) + i.j) + index)))
			continue ;
		varname = ft_substr(*(*((*input) + i.i) + i.j), 0, index);
		if (!varname)
			return (ft_printf_err(ERROR_IE"ft_substr(%*.)", 2));
		new_str = ft_getf("%s\"%s\"", varname,
				*(*((*input) + i.i) + i.j) + index);
		free(varname);
		if (!new_str || last_getf_len(LGL_GET) == -1)
		{
			free(new_str);
			return (ft_printf_err(ERROR_IE"ft_getf(%*.)", 2));
		}
		free(*(*((*input) + i.i) + i.j));
		*(*((*input) + i.i) + i.j) = new_str;
	}
	return (0);
}

int	ft_export_quotes(t_slines *input)
{
	t_ints	i;

	i = (t_ints){.count1 = 0, .count2 = 0, .i = -1};
	while (*((*input) + ++i.i))
	{
		i.j = -1;
		while (*(*((*input) + i.i) + ++i.j))
		{
			if (!ft_strncmp(*(*((*input) + i.i) + i.j), "export", -1))
				if (handle_ecase(input, i) == -1)
					return (-1);
		}
	}
	return (0);
}
