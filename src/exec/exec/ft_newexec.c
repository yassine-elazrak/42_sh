/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_newexec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sid-bell <sid-bell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/27 23:05:30 by sid-bell          #+#    #+#             */
/*   Updated: 2019/12/25 19:42:41 by sid-bell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int		ft_runintern(t_process *process, t_params *params)
{
	int type;

	type = process->arg ? ENV_ENTRY : INTERN_ENTRY;
	if (type == INTERN_ENTRY &&
		!params->forkbuiltins && params->job->foreground)
	{
		ft_getinterns(process, INTERN_ENTRY);
		return (1);
	}
	return (0);
}

int		ft_init_run(t_params *params, t_process *process)
{
	t_function	*func;
	t_process	*p;

	p = params->job->processes;
	if (process->arg && (func = ft_is_builtin(process->arg[0])))
	{
		if ((p && p->next) || params->forkbuiltins)
			return (ft_fork(params, process, func));
		else
		{
			if (!ft_redirect(process->redir))
				return (1);
			if (process->ass)
				return (ft_gettmpvars(process, func));
			else
				return (func(process->arg + 1));
		}
	}
	if (process->ass)
	{
		if (ft_runintern(process, params))
			return (0);
	}
	return (ft_fork(params, process, NULL));
}

void	ft_initexec(int *fds, t_params *params, char *status)
{
	get_shell_cfg(0)->abort = 0;
	fds[0] = -1;
	params->fdscopy[0] = dup(1);
	params->fdscopy[1] = dup(2);
	*status = 0;
}

void	ft_stdin(int *fds)
{
	if (fds[0] > 0)
	{
		dup2(fds[0], 0);
		close(fds[0]);
	}
}

char	ft_exec_job(t_params *params, t_process *process)
{
	int			fds[2];
	char		status;

	ft_initexec(fds, params, &status);
	while (process)
	{
		apply_expansions(process);
		if (get_shell_cfg(0)->abort && (status = 1))
			break ;
		ft_init_proc(process);
		ft_stdin(fds);
		params->pipe_stdin = ft_pipe(fds, process, params->fdscopy);
		if (ft_printheredoc(process))
			continue ;
		if (process->arg || process->ass)
			status = ft_init_run(params, process);
		else if (get_shell_cfg(0)->subshell)
			status = ft_readfile(params);
		else if (process->redir)
			status = !ft_redirect(process->redir);
		process = process->next;
	}
	ft_restore(params);
	return (status);
}
