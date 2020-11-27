/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_findfile.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sid-bell <sid-bell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/05 14:51:13 by sid-bell          #+#    #+#             */
/*   Updated: 2019/12/23 15:47:22 by sid-bell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

char	*getfullpath(char *name)
{
	char	*path;
	char	**entrys;
	int		i;
	char	*fullname;

	fullname = NULL;
	if ((path = ft_getenv("PATH")))
	{
		if ((entrys = ft_strsplit(path, ':')))
		{
			i = 0;
			while (entrys[i])
			{
				fullname = ft_join("%s/%s", entrys[i], name);
				if (!access(fullname, F_OK))
					break ;
				ft_strdel(&fullname);
				i++;
			}
			ft_free_array(entrys);
		}
	}
	return (fullname);
}

int		ft_isexec(char *file, char **error, t_stat *state)
{
	if (!access(file, X_OK))
	{
		if (S_ISREG(state->st_mode))
			return (1);
		else if (S_ISDIR(state->st_mode))
		{
			*error = "42sh: %s: is a directory\n";
			return (0);
		}
	}
	return (0);
}

char	*ft_findfile(char *name, char **error, char add)
{
	char		*file;
	t_params	*p;
	t_stat		state;

	p = ft_getset(0)->params;
	file = NULL;
	if ((file = ft_getvlaue_bykey(name, COMMANDS)))
	{
		if (access(file, F_OK))
			file = NULL;
		else
			file = ft_strdup(file);
	}
	if (ft_strchr(name, '/'))
		file = ft_strdup(name);
	if (!file && ((file = getfullpath(name))) && add)
		ft_addtohashmap(name, file, COMMANDS)->hits = 1;
	if (file && !stat(file, &state))
	{
		if (ft_isexec(file, error, &state))
			return (file);
		*error = "42sh: %s: permission denied\n";
	}
	free(file);
	return (NULL);
}

int		ft_error(char *error, char *name)
{
	ft_set_last_rvalue(127);
	ft_printf_fd(2, error, name);
	return (0);
}

char	*ft_getexecutable(t_process *process, int report)
{
	char	*file;
	char	*error;

	error = NULL;
	if (ft_strlen(process->arg[0]) == 0)
	{
		if (report)
			ft_error("42sh: %s: command not found\n", "");
		return (NULL);
	}
	if ((file = ft_findfile(process->arg[0], &error, 1)))
		return (file);
	else if (!error)
		error = "42sh: %s: command not found\n";
	if (error && report)
		ft_error(error, process->arg[0]);
	return (NULL);
}
