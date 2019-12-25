/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chdir_and_path_handling.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmostafa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/19 15:44:09 by mmostafa          #+#    #+#             */
/*   Updated: 2019/12/25 11:57:33 by mmostafa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int			errors_container(char *curpath, int err)
{
	if (err == 1)
		ft_putstr_fd("42sh: chdir failed\n", 2);
	if (err == 2)
	{
		ft_putstr_fd("42sh: cd: ", 2);
		ft_putstr_fd("permission denied: ", 2);
		ft_putendl_fd(curpath, 2);
	}
	if (err == 3)
	{
		ft_putstr_fd("42sh: cd: ", 2);
		ft_putstr_fd(curpath, 2);
		ft_putstr_fd(" not a directory\n", 2);
	}
	if (err == 4)
	{
		ft_putstr_fd("42sh: cd:", 2);
		ft_putstr_fd(" No such file or directory: ", 2);
		ft_putendl_fd(curpath, 2);
	}
	ft_strdel(&curpath);
	return (-1);
}

static char	*remove_dots(char **paths, t_recipes *recipes)
{
	int		i;

	recipes->curpath = ft_strdup("/");
	i = 0;
	while (paths[i])
	{
		if (paths[i][0] != -1 && i == 0)
			recipes->curpath = ft_join("%f%s", recipes->curpath, paths[i]);
		else if (paths[i][0] != -1 && i != 0)
			recipes->curpath = ft_join("%f/%s", recipes->curpath, paths[i]);
		i++;
	}
	ft_free_array(paths);
	return (recipes->curpath);
}

static char	*operate_dots(char ***paths, char *curpath)
{
	int		i;

	i = 0;
	paths[0] = ft_strsplit(curpath, '/');
	while (paths[0][i])
	{
		if (!ft_strcmp("..", paths[0][i]) && paths[0][i][0] != -1)
		{
			paths[0][i][0] = -1;
			while (paths[0][i][0] == -1 && i)
				i--;
			if (i == 0)
			{
				free(curpath);
				return (ft_strdup("/"));
			}
			else
				paths[0][i][0] = -1;
		}
		if (!ft_strcmp(".", paths[0][i]) && paths[0][i][0] != -1)
			paths[0][i][0] = -1;
		i++;
	}
	free(curpath);
	return (NULL);
}

static char	*curpath_handling(t_recipes *recipes)
{
	if (recipes->curpath[0] != '/')
	{
		if (!ft_strcmp("/", recipes->cwd))
			recipes->curpath = ft_join("%s%f", recipes->cwd, recipes->curpath);
		else if (recipes->options == 'P')
			recipes->curpath = ft_join("%s/%f", recipes->cwd, recipes->curpath);
		else
			recipes->curpath = ft_join("%s/%f",
					get_shell_cfg(0)->pwd, recipes->curpath);
	}
	recipes->curpath = operate_dots(&(recipes->paths), recipes->curpath);
	if (recipes->curpath)
	{
		ft_free_array(recipes->paths);
		return (recipes->curpath);
	}
	return (remove_dots(recipes->paths, recipes));
}

int			chdir_operations(t_recipes *recipes)
{
	if (!stat(recipes->curpath, &recipes->buf))
	{
		if (S_ISDIR(recipes->buf.st_mode))
		{
			if (!access(recipes->curpath, X_OK))
			{
				recipes->curpath = curpath_handling(recipes);
				ft_addtohashmap("OLDPWD", ft_getenv("PWD"), INTERN);
				if (chdir(recipes->curpath) != -1)
				{
					ft_addtohashmap("PWD", recipes->curpath, 1)->exported = 1;
					ft_strdel(&(get_shell_cfg(0)->pwd));
					get_shell_cfg(0)->pwd = ft_strdup(recipes->curpath);
					return (0);
				}
				else
					return (1);
			}
			else
				return (2);
		}
		else
			return (3);
	}
	return (4);
}
