/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fix_redirections.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzhen-cl <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 09:02:47 by kzhen-cl          #+#    #+#             */
/*   Updated: 2025/01/25 09:02:48 by kzhen-cl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	lone_symbols(char *part)
{
	return (!ft_strncmp(part, ">", -1)
		|| !ft_strncmp(part, "<", -1)
		|| !ft_strncmp(part, ">>", -1)
		|| !ft_strncmp(part, "<<", -1));
}

static int	concat(t_rlines *part, int j)
{
	char	*tmp;

	tmp = NULL;
	tmp = ft_strjoin((*part)[j], (*part)[j + 1]);
	if (!tmp)
		return (ft_printf_err("Internal Error:ft_strjoin(%*.)", 2));
	if (ft_rlines_delete(part, j) == -1 || ft_rlines_delete(part, j) == -1)
		return (ft_printf_err("Internal Error:ft_rlines_delete(%*.)", 2));
	if (ft_rlines_add(part, tmp, j) == -1)
	{
		free(tmp);
		return (ft_printf_err("Internal Error:ft_rlines_add(%*.)", 2));
	}
	return (0);
}

static int	fin_fix_redirec(t_rlines *part, int j, char **tmp, int len)
{
	if (len > 1 && (!ft_strncmp((*part)[j] + len - 2, ">>", -1)
		|| !ft_strncmp((*part)[j] + len - 2, "<<", -1)))
	{
		(*part)[j][len - 1] = 0;
		(*part)[j][len - 2] = 0;
	}
	else if (len > 0 && ((*part)[j][len - 1] == '>'
		|| (*part)[j][len - 1] == '<'))
		(*part)[j][len - 1] = 0;
	if (ft_rlines_delete(part, j + 1) == -1)
		return (ft_printf_err("Internal Error:ft_rlines_delete(%*.)", 2));
	if (ft_rlines_add(part, *tmp, j + 1) == -1)
	{
		free(*tmp);
		return (ft_printf_err("Internal Error:ft_rlines_add(%*.)", 2));
	}
	return (0);
}

static int	fix_end_redirec(t_rlines *part, int j)
{
	int		len;
	char	*tmp;

	if (lone_symbols((*part)[j]) || j + 1 == ft_rlines_len(*part))
		return (0);
	tmp = NULL;
	len = ft_strlen((*part)[j]);
	if (len > 1 && !ft_strncmp((*part)[j] + len - 2, ">>", -1))
		tmp = gnlxio_ft_strjoinfree(&(char *){ft_strdup(">>")},
				&(char *){ft_strdup((*part)[j + 1])});
	else if (len > 1 && !ft_strncmp((*part)[j] + len - 2, "<<", -1))
		tmp = gnlxio_ft_strjoinfree(&(char *){ft_strdup("<<")},
				&(char *){ft_strdup((*part)[j + 1])});
	else if (len > 0 && (*part)[j][len - 1] == '>')
		tmp = gnlxio_ft_strjoinfree(&(char *){ft_strdup(">")},
				&(char *){ft_strdup((*part)[j + 1])});
	else if (len > 0 && (*part)[j][len - 1] == '<')
		tmp = gnlxio_ft_strjoinfree(&(char *){ft_strdup("<")},
				&(char *){ft_strdup((*part)[j + 1])});
	else
		return (0);
	if (tmp)
		return (fin_fix_redirec(part, j, &tmp, len));
	return (-1);
}

int	ft_fix_redirections(t_slines *input)
{
	t_ints	i;

	i.i = -1;
	while ((*input)[++(i.i)])
	{
		i.j = -1;
		while ((*input)[i.i][++(i.j)])
			if ((lone_symbols((*input)[i.i][i.j])
				&& (i.j + 1) < ft_rlines_len((*input)[i.i])
				&& concat(&((*input)[i.i]), i.j) == -1)
				|| fix_end_redirec(&((*input)[i.i]), i.j) == -1
				|| ft_split_redirec(&((*input)[i.i]), i.j) == -1)
				return (-1);
	}
	return (0);
}
