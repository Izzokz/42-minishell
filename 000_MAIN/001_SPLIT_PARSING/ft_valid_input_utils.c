/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_valid_input_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pboucher <pboucher@42student.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/16 13:16:53 by pboucher          #+#    #+#             */
/*   Updated: 2025/03/16 13:17:14 by pboucher         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
Makes this kind of case work : ls |>>out cat
*/
void	ft_vi_add_redirec(char *red, char *pipe)
{
	(*red)++;
	*pipe = 0;
}
