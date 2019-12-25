/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getflags.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sid-bell <sid-bell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/27 16:22:38 by sid-bell          #+#    #+#             */
/*   Updated: 2019/10/27 16:24:15 by sid-bell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_getflags(t_printf_params *params)
{
	int		padding;

	if (*params->format == ' ' || ft_isdigit(*params->format))
	{
		if (*params->format == '0')
			params->leading = '0';
		else if (*params->format == ' ')
			params->leading = ' ';
		params->format++;
		if (ft_isdigit(*params->format))
		{
			padding = ft_atoi(params->format);
			params->format += ft_nbrlen(padding, 10);
			params->padding = padding;
		}
	}
}
