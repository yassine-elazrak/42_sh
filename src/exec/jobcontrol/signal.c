/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sid-bell <sid-bell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/08 23:03:34 by sid-bell          #+#    #+#             */
/*   Updated: 2019/12/24 09:19:23 by sid-bell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "jobcontrol.h"

char	*ft_stopped_action(t_job *job)
{
	t_container *container;
	char		*st;

	container = ft_getset(0);
	st = ft_join("[%d] + Stopped \t%s\n", job->id, job->command);
	if (!ft_getjob_byindex(job->id))
		job = ft_cpyjob(job);
	ft_addjob(job, container);
	return (st);
}

void	ft_terminated_action(t_job *job,
		t_job *current, t_process *proc, char **st)
{
	if (job != current || (proc->signaled && WTERMSIG(proc->status) != 2))
	{
		if (WIFEXITED(proc->status) && WEXITSTATUS(proc->status))
			*st = ft_join("[%d] + Exit %d\t\t %s\n", job->id,
				WEXITSTATUS(proc->status), job->command);
		else if (WIFEXITED(proc->status))
			*st = ft_join("[%d]+ Done\t\t%s\n", job->id, job->command);
		else
			*st = ft_join("[%d]+ %s: %d\t\t%s\n", job->id,
				ft_strsignal(WTERMSIG(proc->status)),
					WTERMSIG(proc->status), job->command);
	}
}

void	ft_check_job(t_job *job, t_job *current, t_container *container)
{
	int			status;
	char		*st;
	t_process	*proc;

	st = NULL;
	if (job->notified)
		return ;
	proc = job->processes;
	while (proc->next)
		proc = proc->next;
	status = proc->status;
	if (ft_terminated(job))
		ft_terminated_action(job, current, proc, &st);
	else if (!job->killed && ft_stoped(job))
		st = ft_stopped_action(job);
	if (st)
		ft_lstadd(&container->notify, ft_lstnew(st, 0));
	job->notified = 1;
	if (job->killed && job != current)
		ft_deljob(job, container);
}

void	ft_check_jobs_status(t_job *current)
{
	t_list		*list;
	t_job		*job;
	t_container	*container;
	t_list		*next;

	container = ft_getset(NULL);
	if (current)
		return (ft_check_job(current, current, container));
	list = container->list;
	while (list)
	{
		next = list->next;
		job = list->content;
		if (job)
			ft_check_job(job, current, container);
		list = next;
	}
}

void	ft_sigchld(int sig)
{
	int		status;
	pid_t	pid;

	while (sig == SIGCHLD)
	{
		if ((pid = waitpid(-1, &status, WNOHANG | WUNTRACED)) > 0)
			ft_change_state(NULL, pid, status);
		else
			break ;
	}
	ft_check_jobs_status(NULL);
}
