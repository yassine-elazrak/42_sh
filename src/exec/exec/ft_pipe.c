/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sid-bell <sid-bell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/22 12:08:10 by sid-bell          #+#    #+#             */
/*   Updated: 2019/12/25 19:42:03 by sid-bell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int		ft_pipe(int *pipefd, t_process *process, int *fd)
{
	pipefd[0] = -1;
	pipefd[1] = -1;
	dup2(fd[0], 1);
	dup2(fd[1], 2);
	if ((process->flag == PIPE && process->next) || process->heredoc)
	{
		pipe(pipefd);
		dup2(pipefd[1], 1);
		close(pipefd[1]);
	}
	return (pipefd[0]);
}

int		ft_printheredoc(t_process *process)
{
	if (process->heredoc)
	{
		ft_printf_fd(1, "%s\n", process->heredoc);
		free(process->heredoc);
		process->heredoc = NULL;
		return (1);
	}
	return (0);
}
