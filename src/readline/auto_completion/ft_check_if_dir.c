/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_if_dir.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oherba <oherba@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/24 15:29:13 by oherba            #+#    #+#             */
/*   Updated: 2019/12/25 17:06:49 by oherba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int		ft_path_dir(char **to_complete, char **old_to_complete, char **path)
{
	char		*home_dir;
	struct stat	st;
	char		*tmp;

	tmp = NULL;
	if ((*to_complete)[0] == '~')
	{
		if ((home_dir = ft_getenv("HOME")))
		{
			*(old_to_complete) = ft_strdup(*to_complete);
			*to_complete = ft_strjoin(home_dir, &((*to_complete)[1]));
		}
	}
	if (*to_complete && (!stat(*to_complete, &st) && (S_ISDIR(st.st_mode))))
	{
		*path = ft_strdup(*to_complete);
		ft_strdel(old_to_complete);
		return (2);
	}
	return (0);
}

int		ft_check_if_is_dir(char **path, char **old_to_complete,
	char **new_to_complete, char **tilda)
{
	struct stat	st;
	int			i;

	i = 0;
	if (*path && !stat(*path, &st))
	{
		if (S_ISDIR(st.st_mode))
		{
			if (*old_to_complete)
			{
				i = ft_strlen(*old_to_complete) -
					ft_strlen(*new_to_complete);
				*tilda = ft_strsub(*old_to_complete, 0, i);
				ft_strdel(old_to_complete);
			}
			return (1);
		}
	}
	return (0);
}

int		ft_if_is_dir_2(char **to_complete, char **path,
	char **new_to_complete, char **tilda)
{
	int		i;
	char	*old_to_complete;
	char	*tmp;
	int		n;

	tmp = *to_complete;
	old_to_complete = NULL;
	i = 0;
	if (ft_path_dir(to_complete, &old_to_complete, path) == 2)
		return (ft_free_return_2(&tmp, *to_complete, 2));
	*new_to_complete = ft_strrchr(*to_complete, '/');
	if (*new_to_complete == NULL)
		return (ft_free_return_2(&tmp, *to_complete, 0));
	else
	{
		(*new_to_complete)++;
		i = ft_strlen(*to_complete) - ft_strlen(*new_to_complete);
		*path = ft_strsub(*to_complete, 0, i);
	}
	n = ft_check_if_is_dir(path, &old_to_complete, new_to_complete, tilda);
	if (tmp != *to_complete)
		free(tmp);
	return (n);
}

int		ft_if_is_dir(char *to_complete, char **path,
		char **new_to_complete, char **tilda)
{
	int		i;
	char	*old_to_complete;
	int		n;
	char	*tmp;

	old_to_complete = NULL;
	i = 0;
	if (ft_path_dir(&to_complete, &old_to_complete, path) == 2)
		return (ft_free_return(&to_complete, 2));
	if ((tmp = ft_strrchr(to_complete, '/')))
		tmp++;
	*new_to_complete = ft_strdup(tmp);
	if (*new_to_complete == NULL)
		ft_free_return(&to_complete, 0);
	else
	{
		i = ft_strlen(to_complete) - ft_strlen(*new_to_complete);
		*path = ft_strsub(to_complete, 0, i);
	}
	n = ft_check_if_is_dir(path, &old_to_complete, new_to_complete, tilda);
	if (get_shell_cfg(0)->init->to_complete != to_complete)
		free(to_complete);
	return (n);
}
