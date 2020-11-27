/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_deljob.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sid-bell <sid-bell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/10 02:57:49 by sid-bell          #+#    #+#             */
/*   Updated: 2019/12/22 17:24:06 by sid-bell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "jobcontrol.h"

void	ft_del(t_list *prev, t_list *list, t_container *container)
{
	t_list	*l;

	container->current = NULL;
	if (!prev && !list->next)
	{
		container->prev = NULL;
		return ;
	}
	container->current = container->prev;
	container->prev = NULL;
	l = ft_getset(0)->list;
	while (l)
	{
		if (l != list && l->content != container->current)
		{
			container->prev = l->content;
			return ;
		}
		l = l->next;
	}
}

void	ft_deljob(t_job *job, t_container *container)
{
	t_list		*list;
	t_job		*jb;
	t_list		*prev;

	list = container->list;
	prev = NULL;
	while (list)
	{
		jb = list->content;
		if (jb->pgid == job->pgid)
		{
			ft_del(prev, list, container);
			if (prev)
				prev->next = list->next;
			else
				container->list = container->list->next;
			ft_free_job(jb);
			free(list);
			return ;
		}
		prev = list;
		list = list->next;
	}
}
