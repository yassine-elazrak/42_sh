/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_rd_wr_ex.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sid-bell <sid-bell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/05 13:29:29 by sid-bell          #+#    #+#             */
/*   Updated: 2019/12/05 13:29:35 by sid-bell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int		ft_rwx(int id, char *file)
{
	struct stat	st;

	if (!file)
		return (0);
	if (!lstat(file, &st))
	{
		if (id == 11)
			return (st.st_mode & S_IRUSR ? 0 : 1);
		if (id == 12)
			return (st.st_mode & S_IWUSR ? 0 : 1);
		return (st.st_mode & S_IXUSR ? 0 : 1);
	}
	return (1);
}
