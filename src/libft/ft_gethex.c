/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_gethex.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sid-bell <sid-bell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/27 16:26:34 by sid-bell          #+#    #+#             */
/*   Updated: 2019/10/27 16:27:18 by sid-bell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_gethex(t_printf_params *param)
{
	unsigned long long	result;
	char				*str;
	char				*tmp;

	result = va_arg(*param->list, unsigned long long);
	str = ft_itoa(result, 16);
	ft_padding(param->padding, &str, param->leading);
	tmp = param->str;
	param->str = ft_strjoin(param->str, str);
	free(tmp);
	free(str);
}
