/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_rvalue.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sid-bell <sid-bell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/18 16:03:21 by sid-bell          #+#    #+#             */
/*   Updated: 2019/12/20 18:40:11 by sid-bell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "jobcontrol.h"

void	ft_set_last_rvalue(uint8_t rvalue)
{
	t_container *container;
	char		*nbr;

	nbr = ft_itoa(rvalue, 10);
	ft_addtohashmap("?", nbr, INTERN);
	container = ft_getset(NULL);
	container->last_status = rvalue;
	free(nbr);
}

uint8_t	ft_get_last_rvalue(void)
{
	t_container *container;

	container = ft_getset(NULL);
	return (container->last_status);
}
