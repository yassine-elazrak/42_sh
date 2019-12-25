/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tild_expansion.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoyassin <yoyassin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/04 19:30:27 by mmostafa          #+#    #+#             */
/*   Updated: 2019/12/22 21:25:53 by yoyassin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

char	*tild_expan(char *tild_str)
{
	struct passwd	*pw;
	char			*home_dir;
	char			*user_name;

	if (!ft_strcmp(tild_str, "~"))
	{
		if (!(home_dir = ft_getenv("HOME")))
			home_dir = getpwnam(ft_getusername())->pw_dir;
		return (ft_strdup(home_dir));
	}
	user_name = ft_strsub(tild_str, 1, ft_strlen(tild_str) - 1);
	if (!(pw = getpwnam(user_name)))
	{
		free(user_name);
		return (ft_strdup(tild_str));
	}
	free(user_name);
	return (ft_strdup(pw->pw_dir));
}
