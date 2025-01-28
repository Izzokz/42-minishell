/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pboucher <pboucher@42student.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 16:06:14 by pboucher          #+#    #+#             */
/*   Updated: 2025/01/28 16:31:39 by pboucher         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_pwd(t_data *data, t_rlines cmd)
{
	char	*path;
	int		i;

	(void)cmd;
	i = 0;
	while (data->envp[i])
	{
		if (!ft_strncmp(data->envp[i], "PWD=", 4))
			break;
		i++;
	}
	path = ft_substr(data->envp[i], 4, -1);
	ft_printf("%s\n", path);
	free(path);
}
