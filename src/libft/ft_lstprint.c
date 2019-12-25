/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstprint.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sid-bell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/17 05:44:11 by sid-bell          #+#    #+#             */
/*   Updated: 2018/10/17 05:46:55 by sid-bell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstprint(t_list *list, int type)
{
	while (list)
	{
		if (type == _CHAR)
			ft_putstr((char *)list->content);
		else if (type == _INT)
			ft_putnbr(*((int*)list->content));
		list = list->next;
		ft_putchar('\n');
	}
}
