/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_readfile.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sid-bell <sid-bell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/22 12:11:18 by sid-bell          #+#    #+#             */
/*   Updated: 2019/12/23 22:45:44 by sid-bell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int		ft_readfile(t_params *params)
{
	char		*line;
	t_process	*proc;
	int			fd;
	char		*file;

	if (!params->job->processes->next)
	{
		proc = params->job->processes;
		if (proc->redir && proc->redir->file && proc->redir->type == O_RDONLY
			&& !proc->redir->next)
		{
			file = proc->redir->file;
			if ((fd = open(file, O_RDONLY)) < 0)
			{
				ft_printf_fd(2, "42sh: no such file or directory: %s\n", file);
				return (1);
			}
			while (get_next_line(fd, '\n', &line) > 0)
				ft_printf_fd(1, "%f\n", line);
		}
	}
	return (0);
}
