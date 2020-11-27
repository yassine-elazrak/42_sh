/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmostafa <mmostafa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/02 12:08:31 by sid-bell          #+#    #+#             */
/*   Updated: 2019/12/25 17:56:45 by mmostafa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

char	*cdpath_concatenation(char *cdpath, char *directory)
{
	char		**cdpaths;
	char		*path;
	struct stat	buf;
	int			i;

	if (!(cdpaths = ft_strsplit(cdpath, ':')))
		return (NULL);
	i = -1;
	while (cdpaths[++i])
	{
		if (cdpaths[i][ft_strlen(cdpaths[i]) - 1] != '/')
			path = ft_join("%s/%s", cdpaths[i], directory);
		else
			path = ft_join("%s%s", cdpaths[i], directory);
		if (!stat(path, &buf) && S_ISDIR(buf.st_mode))
		{
			ft_free_array(cdpaths);
			return (path);
		}
		ft_strdel(&path);
	}
	ft_free_array(cdpaths);
	return (NULL);
}

char	*ft_home(t_recipes *recipes)
{
	if (recipes->home)
		return (ft_strdup(recipes->home));
	ft_putstr_fd("42sh: HOME not set\n", 2);
	return (NULL);
}

char	*ft_treat_single_arg(t_recipes *recipes, char **cmd)
{
	if (cmd[0][0] == '-' && cmd[0][1] == '\0')
	{
		if (recipes->oldpwd)
			return (ft_strdup(recipes->oldpwd));
		ft_putstr_fd("42sh: OLDPWD not set\n", 2);
		return (NULL);
	}
	return (ft_strdup(cmd[0]));
}

int		print_error(void)
{
	ft_putstr_fd("42sh: too many arguments\n", 2);
	return (1);
}

int		ft_cd(char **cmd)
{
	int			i;
	t_recipes	recipes;
	char		options[127];
	size_t		len;

	if ((i = ft_getopt(cmd, options, "LP")) < 0)
	{
		ft_printf_fd(2, "42sh: cd: -%c: invalid option\n", -i);
		return (1);
	}
	recipes_preparations(&recipes);
	if (i - 2 >= 0 && !ft_strcmp(cmd[i - 1], "--"))
		recipes.options = cmd[i - 2][ft_strlen(cmd[i - 2]) - 1];
	else if (i - 1 >= 0)
		recipes.options = cmd[i - 1][ft_strlen(cmd[i - 1]) - 1];
	if ((len = ft_arraylen(cmd + i)) > 1)
		return (print_error());
	else if (len == 0)
		recipes.curpath = ft_home(&recipes);
	else if (len == 1)
		recipes.curpath = ft_treat_single_arg(&recipes, cmd + i);
	return (cd_wheels(&recipes));
}
