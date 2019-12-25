/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getjobstatus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sid-bell <sid-bell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/06 14:34:19 by sid-bell          #+#    #+#             */
/*   Updated: 2019/12/20 14:56:17 by sid-bell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

uint8_t	ft_getjobstatus(t_process *pr)
{
	uint8_t	status;

	status = 0;
	while (pr)
	{
		if (pr->pid > 0)
			status = WEXITSTATUS(pr->status);
		else
			status = 0;
		pr = pr->next;
	}
	return (status);
}
