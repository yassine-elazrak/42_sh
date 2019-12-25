/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_usergroup.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sid-bell <sid-bell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/05 13:28:13 by sid-bell          #+#    #+#             */
/*   Updated: 2019/12/05 13:28:20 by sid-bell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int		ft_usergroup(int id, char *file)
{
	struct stat	st;

	if (!file)
		return (0);
	if (!lstat(file, &st))
	{
		if (id == 9)
			return (st.st_mode & S_ISUID ? 0 : 1);
		return (st.st_mode & S_ISGID ? 0 : 1);
	}
	return (1);
}
