/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fg.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sid-bell <sid-bell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/10 03:01:02 by sid-bell          #+#    #+#             */
/*   Updated: 2019/12/22 17:17:58 by sid-bell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "jobcontrol.h"

void	ft_resetstatus(t_job *job)
{
	t_process	*proc;

	job->suspended = 0;
	job->foreground = 1;
	proc = job->processes;
	while (proc)
	{
		if (!proc->exited)
		{
			proc->stoped = 0;
			proc->signaled = 0;
			proc->status = 0;
		}
		proc = proc->next;
	}
}

int		ft_fg(char **arg)
{
	t_job	*job;

	if (!(job = ft_getjob(*arg, "fg")))
		return (1);
	ft_printf("%s\n", job->command);
	ft_resetstatus(job);
	signal(SIGCHLD, SIG_DFL);
	if (!killpg(job->pgid, SIGCONT))
	{
		if (tcsetpgrp(0, job->pgid) != 0)
		{
			ft_printf("can't setpgrp :-(\n");
			return (1);
		}
		ft_addjob(job, ft_getset(0));
		ft_wait(job, 0);
	}
	else
	{
		ft_printf("unable to continue job %s\n", job->command);
		ft_deljob(job, ft_getset(NULL));
		return (1);
	}
	return (0);
}
