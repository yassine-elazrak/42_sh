/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_tools.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmostafa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/19 15:54:19 by mmostafa          #+#    #+#             */
/*   Updated: 2019/12/25 19:33:35 by mmostafa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	recipes_preparations(t_recipes *recipes)
{
	char	tmp[4097];

	tmp[4096] = '\0';
	recipes->oldpwd = ft_getenv("OLDPWD");
	recipes->home = ft_getenv("HOME");
	recipes->cwd = getcwd(tmp, 4097);
	recipes->pwd = get_shell_cfg(0)->pwd;
	recipes->cdpath = ft_getvlaue_bykey("CDPATH", INTERN);
	recipes->curpath = NULL;
	recipes->options = 0;
	recipes->error = 0;
	recipes->mute = 0;
}
