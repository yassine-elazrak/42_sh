/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   job_builtins.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sid-bell <sid-bell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/02 17:44:55 by sid-bell          #+#    #+#             */
/*   Updated: 2019/12/19 18:07:20 by sid-bell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "jobcontrol.h"

t_job	*ft_getjob(char *arg, char *caller)
{
	t_container *container;
	int			jobid;
	t_job		*job;

	jobid = -1;
	if (arg)
	{
		if (*arg == '%')
			arg++;
		if (*arg)
			jobid = ft_atoi(arg);
	}
	container = ft_getset(NULL);
	if (jobid == -1)
		return (container->current);
	if (!(job = ft_getjob_byindex(jobid)))
	{
		ft_printf_fd(2, "%s %d: no such job\n", caller, jobid);
		return (NULL);
	}
	return (job);
}
