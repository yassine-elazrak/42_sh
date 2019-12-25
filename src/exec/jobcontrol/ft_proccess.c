/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_proccess.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sid-bell <sid-bell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/10 03:02:45 by sid-bell          #+#    #+#             */
/*   Updated: 2019/11/28 16:58:52 by sid-bell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "jobcontrol.h"

t_job		*ft_pid_lookup(pid_t pid, t_process **procc)
{
	t_list		*list;
	t_process	*proc;

	list = ft_getset(NULL)->list;
	while (list)
	{
		proc = ((t_job *)list->content)->processes;
		while (proc)
		{
			if (proc->pid == pid)
			{
				*procc = proc;
				return (list->content);
			}
			proc = proc->next;
		}
		list = list->next;
	}
	return (NULL);
}

void		ft_addprocess(t_process *process, pid_t pid)
{
	process->pid = pid;
	process->exited = 0;
	process->stoped = 0;
	process->signaled = 0;
	process->status = 0;
}

t_process	*ft_getproc_byjob(t_job *job, pid_t pid)
{
	t_process	*proc;

	proc = job->processes;
	while (proc)
	{
		if (proc->pid == pid)
			return (proc);
		proc = proc->next;
	}
	return (NULL);
}

t_process	*ft_findjob(int pid)
{
	t_list			*lst;
	t_process		*proc;

	lst = ft_getset(NULL)->list;
	while (lst)
	{
		if ((proc = ft_getproc_byjob(lst->content, pid)))
			return (proc);
		lst = lst->next;
	}
	return (NULL);
}
