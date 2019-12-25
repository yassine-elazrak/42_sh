/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_joingroup.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sid-bell <sid-bell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/22 13:53:46 by sid-bell          #+#    #+#             */
/*   Updated: 2019/12/22 13:54:02 by sid-bell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	ft_joingroup(t_params *params, t_process *process)
{
	pid_t pid;

	pid = process->pid;
	if (!params->job->pgid)
		params->job->pgid = pid;
	if (get_shell_cfg(0)->interractive)
		setpgid(pid, params->job->pgid);
}
