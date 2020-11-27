/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sizetest.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sid-bell <sid-bell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/05 13:36:53 by sid-bell          #+#    #+#             */
/*   Updated: 2019/12/05 13:37:05 by sid-bell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int		ft_sizetest(char *file)
{
	struct stat	st;

	if (!file)
		return (0);
	if (!lstat(file, &st))
	{
		return (st.st_size == 0);
	}
	return (1);
}
