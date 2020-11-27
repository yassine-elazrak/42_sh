/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sid-bell <sid-bell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/18 10:05:39 by sid-bell          #+#    #+#             */
/*   Updated: 2019/12/23 21:21:58 by sid-bell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int		ft_promptlen(char *prompt)
{
	size_t	len;
	size_t	i;

	i = 0;
	len = 0;
	while (prompt[i])
	{
		if (prompt[i] == '\e')
		{
			while (prompt[i] != 'm')
				i++;
			i++;
			continue;
		}
		len++;
		i++;
	}
	return (len);
}

char	*ft_getpwd(void)
{
	char	*path;
	char	*home;
	int		len;

	if ((path = ft_getenv("PWD")))
	{
		if ((home = ft_getenv("HOME")))
		{
			len = ft_strlen(home);
			if (ft_strnequ(home, path, len))
			{
				if (*(path + len) == '/')
					path = ft_join("~%s", path + len);
				else
					path = ft_join("~/%s", path + len);
			}
			else
				path = ft_strdup(path);
		}
		else
			path = ft_strdup(path);
	}
	return (path);
}

char	*ft_getprompt(void)
{
	char	*path;
	char	*clr;
	char	*prompt;

	clr = "\e[32m";
	if (ft_get_last_rvalue())
		clr = "\e[31m";
	if ((path = ft_getpwd()))
		prompt = ft_join("%f $> ", path);
	else
		prompt = ft_strdup("$> ");
	return (prompt);
}
