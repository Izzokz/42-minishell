/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipe_split.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pboucher <pboucher@42student.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 16:47:11 by kzhen-cl          #+#    #+#             */
/*   Updated: 2025/03/08 09:57:39 by pboucher         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_edit_split(t_rlines *split, char *line_part, char *ch)
{
	t_ints	i;

	ft_realloc_rlines(split, 1);
	if (!split)
		return (ft_printf_err(ERROR_IE"ft_calloc(%*.)", 2));
	i.len = ft_rlines_len(*split);
	(*split)[i.len] = ft_strdup(line_part);
	if (!(*split)[i.len])
		return (ft_printf_err(ERROR_IE"ft_strdup(%*.)", 2));
	i.count1 = 0;
	i.count2 = 0;
	i.i = -1;
	while ((*split)[i.len][++(i.i)])
	{
		if (!(i.count1 + i.count2) && ft_strchr(ch, (*split)[i.len][i.i]))
			break ;
		else if (!i.count2 && (*split)[i.len][i.i] == '\'')
			i.count1 = !i.count1;
		else if (!i.count1 && (*split)[i.len][i.i] == '"')
			i.count2 = !i.count2;
	}
	while ((*split)[i.len][i.i])
		(*split)[i.len][i.i++] = '\0';
	return (0);
}

static void	*ft_calloc_err(void)
{
	ft_printf_err(ERROR_IE"ft_calloc()", 2);
	return (NULL);
}

/*
i.count1 determines if a single quote is opened
i.count2 determines if a double quote is opened
*/
static t_rlines	ft_mini_split(char *line, char *ch)
{
	t_ints		i;
	t_rlines	split;

	i.count1 = 0;
	i.count2 = 0;
	split = ft_calloc(1, sizeof(char *));
	i.i = -1;
	if (!split)
		return (ft_calloc_err());
	while (line[++(i.i)])
	{
		if ((!(i.count1 + i.count2) && !ft_strchr(ch, line[i.i])
				&& (i.i == 0 || ft_strchr(ch, line[i.i - 1]))
				&& ft_edit_split(&split, line + i.i, ch) == -1))
			return (ft_calloc_err());
		else if (!i.count2 && line[i.i] == '\'')
			i.count1 = !i.count1;
		else if (!i.count1 && line[i.i] == '"')
			i.count2 = !i.count2;
	}
	return (split);
}

static void	*ft_free_input(t_rlines *pre_split, t_slines *split)
{
	ft_free_rlines(pre_split);
	return (ft_free_slines(split));
}

t_slines	ft_pipe_split(char *line)
{
	t_rlines	pre_split;
	t_slines	split;
	int			i;

	if (ft_strlen(line) == 0)
		return (NULL);
	pre_split = ft_mini_split(line, "|");
	if (invalid_rlines_free(&pre_split))
		return (NULL);
	split = ft_calloc(ft_rlines_len(pre_split) + 1, sizeof(t_rlines));
	if (!split)
		return (ft_calloc_err());
	i = -1;
	while (pre_split[++i])
	{
		split[i] = ft_mini_split(pre_split[i], " \t\n\v\f\r");
		if (!split[i])
			return (ft_free_input(&pre_split, &split));
	}
	ft_free_rlines(&pre_split);
	if (ft_fix_redirections(&split) == -1
		|| ft_fix_order(&split) == -1
		|| ft_expand_slines(&split) == -1)
		return (ft_free_slines(&split));
	return (split);
}
