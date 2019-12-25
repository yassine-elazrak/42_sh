/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_jobs.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sid-bell <sid-bell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/10 03:02:19 by sid-bell          #+#    #+#             */
/*   Updated: 2019/12/22 12:52:10 by sid-bell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "jobcontrol.h"

static int	ft_printerr(char c)
{
	ft_printf_fd(2, "42sh: jobs: -%c: invalid option\n", -c);
	ft_printf_fd(2, "42sh: usage: export [-pl]\n", -c);
	return (1);
}

void		ft_printjob(t_job *job, char *options)
{
	char		sign;
	t_container	*container;

	container = ft_getset(0);
	sign = ' ';
	sign = job == container->current ? '+' : ' ';
	sign = job == container->prev ? '-' : sign;
	if (options['l'])
		ft_printf("[%d] %c %d %s %s\n",
				job->id,
				sign,
				job->pgid,
				job->suspended ? "Stoped" : "Running",
				job->command);
	else if (options['p'])
		ft_printf("%d\n", job->pgid);
	else
		ft_printf("[%d] %c %s\t\t%s\n",
				job->id,
				sign,
				job->suspended ? "Stoped" : "Running",
				job->command);
}

void		ft_printall(char *options)
{
	t_container	*container;
	t_list		*list;
	t_job		*job;

	container = ft_getset(NULL);
	list = container->list;
	while (list)
	{
		job = list->content;
		ft_printjob(job, options);
		list = list->next;
	}
}

int			ft_jobs(char **args)
{
	char	options[127];
	int		i;
	t_job	*job;
	int		rval;

	rval = 0;
	if ((i = ft_getopt(args, options, "pl")) < 0)
		return (ft_printerr(i));
	if (args[i])
	{
		while (args[i])
		{
			if ((job = ft_getjob(args[i], "jobs")))
				ft_printjob(job, options);
			else
				rval = 1;
			i++;
		}
	}
	else
		ft_printall(options);
	return (rval);
}
