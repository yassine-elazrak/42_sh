/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execbg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sid-bell <sid-bell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/22 12:33:03 by sid-bell          #+#    #+#             */
/*   Updated: 2019/12/22 12:33:13 by sid-bell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

char	ft_run_in_sub(t_process *p)
{
	while (p)
	{
		if (p->flag == OR || p->flag == AND)
			return (1);
		p = p->next;
	}
	return (0);
}

t_job	*ft_list(t_process *pr)
{
	t_job		*job;
	t_job		*new;
	t_job		*head;

	job = NULL;
	head = NULL;
	while (pr)
	{
		new = ft_newjob(0, 0);
		new->flag = pr->flag;
		new->processes->arg = NULL;
		new->processes->ass = NULL;
		new->processes->holder = pr->holder;
		new->command = pr->arg ? ft_strdup(pr->arg[0]) : NULL;
		if (job)
			job->next = new;
		else
			head = new;
		job = new;
		pr = pr->next;
	}
	return (head);
}

void	ft_execbg(t_job *job)
{
	pid_t		pid;
	t_job		*jb;

	if (!(pid = fork()))
	{
		ft_resetsignals();
		pid = getpid();
		setpgid(pid, pid);
		get_shell_cfg(0)->interractive = 0;
		ft_getset(0)->list = NULL;
		ft_getset(0)->current = NULL;
		ft_getset(0)->prev = NULL;
		job = ft_list(job->processes);
		exit(exec(job));
	}
	setpgid(pid, pid);
	jb = ft_newjob(pid, 0);
	jb->pgid = pid;
	ft_printf("[%d] %d\n", jb->id, jb->pgid);
	jb->command = ft_strdup(job->command);
	ft_addjob(jb, ft_getset(0));
}
