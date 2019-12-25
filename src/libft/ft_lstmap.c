/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sid-bell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/13 02:14:53 by sid-bell          #+#    #+#             */
/*   Updated: 2018/10/13 19:03:08 by sid-bell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list *new;
	t_list *next;

	if (!lst || !f || !(new = ft_lstnew(f(lst)->content, f(lst)->content_size)))
		return (NULL);
	next = 0;
	if (lst->next)
		next = ft_lstmap(lst->next, f);
	new->next = next;
	return (new);
}
