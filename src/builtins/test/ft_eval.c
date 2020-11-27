/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_eval.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sid-bell <sid-bell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/05 13:33:08 by sid-bell          #+#    #+#             */
/*   Updated: 2019/12/21 15:16:59 by sid-bell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int		ft_eval(int id, char *file)
{
	struct stat	st;
	int			i;
	int			*test;

	test = ft_getset(0)->test;
	i = 0;
	if (!file)
		return (0);
	if (!lstat(file, &st))
	{
		if (test[id - 1])
		{
			i = ((st.st_mode & S_IFMT) == test[id - 1]) ? 0 : 1;
			return (i);
		}
		return (0);
	}
	return (1);
}

void	ft_setoprations(void)
{
	int		*test;

	test = ft_getset(0)->test;
	test[0] = S_IFBLK;
	test[1] = S_IFCHR;
	test[2] = S_IFDIR;
	test[3] = 0;
	test[4] = S_IFREG;
	test[5] = S_IFLNK;
	test[6] = S_IFIFO;
	test[7] = S_IFSOCK;
}
