/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pboucher <pboucher@42student.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 15:01:50 by pboucher          #+#    #+#             */
/*   Updated: 2025/01/28 16:35:29 by pboucher         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_cd(t_data *data, t_rlines cmd)
{
	char	*path;
	int		i;

	i = 0;
	(void)cmd;
	while (data->envp[i])
	{
		if (!ft_strncmp(data->envp[i], "HOME=", 5))
			break ;
		i++;
	}
	path = ft_substr(data->envp[i], 5, -1);
	chdir(path);
	free(path);
}
