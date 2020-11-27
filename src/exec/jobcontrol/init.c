/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sid-bell <sid-bell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/02 16:48:10 by sid-bell          #+#    #+#             */
/*   Updated: 2019/12/24 19:39:27 by sid-bell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "jobcontrol.h"

t_container	*ft_getset(t_container *container)
{
	static	t_container *c;

	if (container)
		c = container;
	return (c);
}

void		ft_init_jobcontrol(void)
{
	t_container		*container;
	pid_t			pid;
	pid_t			pgid;

	pid = getpgrp();
	while (1)
	{
		pgid = tcgetpgrp(0);
		if (pgid == pid)
			break ;
		kill(pid, SIGTTIN);
	}
	container = ft_memalloc(sizeof(t_container));
	container->list = NULL;
	container->current = NULL;
	container->notify = NULL;
	container->prev = NULL;
	container->last_aliases = NULL;
	container->last_status = 0;
	container->time_to_exit = 1;
	container->jobs = NULL;
	container->term = NULL;
	ft_getset(container);
	signal(SIGCHLD, ft_sigchld);
	ft_ignore_signlas();
}

void		ft_jobs_in_child(t_job *job)
{
	if (get_shell_cfg(0)->interractive)
	{
		if (job->pgid)
			setpgid(getpid(), job->pgid);
		else
			setpgid(getpid(), getpid());
	}
	ft_resetsignals();
}
