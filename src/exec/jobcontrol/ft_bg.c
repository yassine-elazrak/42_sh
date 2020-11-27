/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bg.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sid-bell <sid-bell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/10 03:01:46 by sid-bell          #+#    #+#             */
/*   Updated: 2019/12/19 17:52:11 by sid-bell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "jobcontrol.h"

int		ft_bg(char **arg)
{
	t_job	*job;

	if (!(job = ft_getjob(*arg, "bg")))
		return (1);
	job->suspended = 0;
	job->foreground = 0;
	ft_printf("[%d]+ %s\n", job->id, job->command);
	ft_resetstatus(job);
	if (killpg(job->pgid, SIGCONT))
	{
		ft_printf("unable to continue job %s\n", job->command);
		ft_deljob(job, ft_getset(NULL));
		return (1);
	}
	return (0);
}
