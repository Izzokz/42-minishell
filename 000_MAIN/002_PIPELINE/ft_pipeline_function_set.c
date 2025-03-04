/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipeline_function_set.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzhen-cl <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 13:31:54 by kzhen-cl          #+#    #+#             */
/*   Updated: 2025/01/28 13:31:56 by kzhen-cl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_pipeline	*ft_new_pipeline(int (*func)(t_data *, void *), void *param,
	void (*free)())
{
	t_pipeline	*pipeline;

	if (!param || !func || !free)
		return (NULL);
	pipeline = malloc(sizeof(t_pipeline));
	if (!pipeline)
		return (NULL);
	pipeline->func = func;
	pipeline->free = free;
	pipeline->param = param;
	pipeline->next = NULL;
	return (pipeline);
}

void	ft_destroy_pipeline(t_pipeline *start)
{
	t_pipeline	*tmp;

	while (start)
	{
		tmp = start->next;
		start->free(start->param);
		free(start);
		start = tmp;
	}
}

void	ft_destroy_all_pipelines(t_pipeline ***all)
{
	int	i;

	if (!(*all))
		return ;
	i = -1;
	while ((*all)[++i])
		ft_destroy_pipeline((*all)[i]);
	free(*all);
	*all = NULL;
}

int	ft_add_pipeline(t_pipeline *start, int (*func)(t_data *, void *),
	void *param, void (*free)())
{
	if (!start)
		return (0);
	while (start->next)
		start = start->next;
	start->next = ft_new_pipeline(func, param, free);
	return (!!start->next);
}

int	ft_add_front_pipeline(t_pipeline **start,
	int (*func)(t_data *, void *), void *param, void (*free)())
{
	t_pipeline	*new_start;

	if (!(*start))
		return (0);
	new_start = ft_new_pipeline(func, param, free);
	if (!new_start)
		return (0);
	new_start->next = *start;
	*start = new_start;
	return (1);
}
