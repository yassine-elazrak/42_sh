/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cpyjob.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sid-bell <sid-bell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/17 18:25:59 by sid-bell          #+#    #+#             */
/*   Updated: 2019/12/20 14:57:03 by sid-bell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

t_process	*ft_cpyproc(t_process *proc)
{
	t_process	*new;

	new = ft_memalloc(sizeof(t_process));
	new->exited = proc->exited;
	new->flag = proc->flag;
	new->next = NULL;
	new->pid = proc->pid;
	new->status = proc->status;
	new->stoped = proc->stoped;
	new->ass = NULL;
	new->arg = NULL;
	return (new);
}

void		ft_getprocs(t_job *job, t_job *new)
{
	t_process	*oldproc;
	t_process	*newproc;
	t_process	*proc;
	t_process	*head;

	oldproc = job->processes;
	newproc = NULL;
	head = NULL;
	while (oldproc)
	{
		proc = ft_cpyproc(oldproc);
		if (newproc)
			newproc->next = proc;
		else
			head = proc;
		newproc = proc;
		oldproc = oldproc->next;
	}
	newproc->next = NULL;
	new->processes = head;
}

t_job		*ft_cpyjob(t_job *job)
{
	t_job		*new;

	new = ft_memalloc(sizeof(t_job));
	ft_getprocs(job, new);
	new->command = ft_strdup(job->command);
	new->flag = job->flag;
	new->foreground = job->foreground;
	new->killed = job->killed;
	new->id = job->id;
	new->pgid = job->pgid;
	new->notified = job->notified;
	new->next = NULL;
	new->return_val = job->return_val;
	new->suspended = job->suspended;
	return (new);
}
