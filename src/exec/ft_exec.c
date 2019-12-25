/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sid-bell <sid-bell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/18 17:04:30 by sid-bell          #+#    #+#             */
/*   Updated: 2019/12/24 19:37:33 by sid-bell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	ft_init_exec(void)
{
	ft_restorestd(1, 1, 1);
	ft_init_jobcontrol();
}

int		ft_exec_wait(t_params *p, t_job *job)
{
	uint8_t	status;

	p->forkbuiltins = job->flag == BG || job->processes->next;
	signal(SIGCHLD, SIG_DFL);
	status = ft_exec_job(p, job->processes);
	ft_wait(job, status);
	signal(SIGCHLD, ft_sigchld);
	if (get_shell_cfg(0)->abort)
		return (-1);
	status = !status ? ft_getjobstatus(job->processes) : status;
	return (status);
}

t_job	*ft_and_or(t_job *job, int status)
{
	int			flag;

	if (job->flag == OR || job->flag == AND)
	{
		flag = job->flag;
		while (job && ((job->flag == AND && status)
					|| (job->flag == OR && !status)))
			job = job->next;
	}
	return (job);
}

int		exec(t_job *job)
{
	t_params	p;
	int			status;

	status = 0;
	ft_getset(0)->params = &p;
	ft_getset(0)->jobs = job;
	while (job)
	{
		p.pipe_stdin = -1;
		p.job = job;
		ft_init_job(job);
		if (job->flag == BG && ft_run_in_sub(job->processes))
			ft_execbg(job);
		else
		{
			if ((status = ft_exec_wait(&p, job)) < 0)
				break ;
			job = ft_and_or(job, status);
		}
		job = job->next;
	}
	ft_getset(0)->params = NULL;
	return (status);
}
