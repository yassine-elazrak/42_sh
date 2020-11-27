/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sid-bell <sid-bell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/10 03:06:16 by sid-bell          #+#    #+#             */
/*   Updated: 2019/12/22 09:58:57 by sid-bell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	ft_free_array(char **args)
{
	int i;

	i = 0;
	while (args && args[i])
	{
		free(args[i]);
		i++;
	}
	free(args);
}

void	ft_freered(t_redir *red)
{
	t_redir *next;

	while (red)
	{
		free(red->file);
		next = red->next;
		free(red);
		red = next;
	}
}

void	ft_freeprocs(t_process *proc)
{
	t_process *next;

	while (proc)
	{
		ft_free_array(proc->arg);
		ft_free_array(proc->ass);
		free(proc->heredoc);
		ft_freered(proc->redir);
		ft_free_array(proc->holder);
		proc->holder = NULL;
		next = proc->next;
		free(proc);
		proc = next;
	}
}

void	ft_free_job(t_job *job)
{
	t_job	*next;

	while (job)
	{
		next = job->next;
		ft_memdel((void *)&job->command);
		ft_freeprocs(job->processes);
		free(job);
		job = next;
	}
}
