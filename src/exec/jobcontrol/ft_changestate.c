/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_changestate.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sid-bell <sid-bell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/16 21:51:22 by sid-bell          #+#    #+#             */
/*   Updated: 2019/12/23 21:28:01 by sid-bell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int		ft_stoped(t_job *job)
{
	t_process		*proc;

	proc = job->processes;
	while (proc)
	{
		if (!proc->stoped && !proc->exited)
			return (0);
		proc = proc->next;
	}
	job->suspended = 1;
	return (1);
}

int		ft_terminated(t_job *job)
{
	t_process		*proc;

	proc = job->processes;
	while (proc)
	{
		if (proc->pid > 0 && !proc->exited)
			return (0);
		proc = proc->next;
	}
	job->killed = 1;
	return (1);
}

void	ft_getstat(t_process *proc, int status)
{
	proc->status = status;
	proc->signaled = WIFSIGNALED(status);
	proc->stoped = WIFSTOPPED(status);
	proc->exited = !proc->stoped;
}

void	ft_change_state(t_job *job, pid_t pid, int status)
{
	t_process	*proc;

	if (job && (proc = ft_getproc_byjob(job, pid)))
	{
		ft_getstat(proc, status);
		if (proc->signaled && !proc->next && get_shell_cfg(0)->interractive)
		{
			if (WTERMSIG(proc->status) != 2 && ft_print_termsig(status))
			{
				job->notified = 1;
				return ;
			}
		}
	}
	else
	{
		proc = NULL;
		job = ft_pid_lookup(pid, &proc);
		if (proc)
			ft_getstat(proc, status);
	}
	if (job)
		job->notified = 0;
}
