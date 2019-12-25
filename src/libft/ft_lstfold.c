/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstfold.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sid-bell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/17 06:37:00 by sid-bell          #+#    #+#             */
/*   Updated: 2018/10/17 19:18:03 by sid-bell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstfold(t_list *list)
{
	long int result;

	result = 0;
	while (list)
	{
		result += *((int*)list->content);
		list = list->next;
	}
	return (result);
}
