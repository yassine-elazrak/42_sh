/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_wait.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sid-bell <sid-bell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/10 03:03:26 by sid-bell          #+#    #+#             */
/*   Updated: 2019/12/22 12:59:59 by sid-bell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	ft_get_term(t_job *job)
{
	t_shell	*container;

	ft_set_last_rvalue(ft_getjobstatus(job->processes));
	container = get_shell_cfg(0);
	ft_check_jobs_status(job);
	if (container->interractive)
	{
		tcsetattr(0, TCSANOW, &get_shell_cfg(0)->init->term_copy);
		if (tcsetpgrp(0, getpgrp()) == -1)
		{
			ft_printf_fd(2, "42sh : fatal error");
			exit(1);
		}
	}
	if (job->killed)
		ft_deljob(job, ft_getset(0));
}

void	ft_background(t_job *job)
{
	if (job->processes->arg || job->processes->ass)
		job = ft_cpyjob(job);
	ft_addjob(job, ft_getset(NULL));
	if (!get_shell_cfg(0)->subshell)
		ft_printf("[%d] %d\n", job->id, job->pgid);
}

void	ft_wait(t_job *job, int status)
{
	pid_t		pid;

	job->suspended = 0;
	if (!job->pgid)
		return (ft_set_last_rvalue(status));
	if (!job->foreground)
		ft_background(job);
	else
	{
		if (get_shell_cfg(0)->interractive)
			tcsetpgrp(0, job->pgid);
		while (1)
		{
			if ((pid = waitpid(-1, &status, WNOHANG | WUNTRACED)) > 0)
			{
				ft_change_state(job, pid, status);
				if (ft_terminated(job) || ft_stoped(job))
					break ;
			}
		}
		ft_get_term(job);
	}
}
