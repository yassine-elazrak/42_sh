/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printenv.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sid-bell <sid-bell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/25 22:00:41 by sid-bell          #+#    #+#             */
/*   Updated: 2019/12/25 22:00:48 by sid-bell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

char		*ft_escap(char *str)
{
	int		i;
	char	*new;

	if ((!ft_strchr(str, '"') && !ft_strchr(str, '\'')))
		return (ft_strdup(str));
	i = 0;
	new = ft_strdup("");
	while (str[i])
	{
		if (str[i] == '"')
			new = ft_join("%f\\\"", new);
		else if (str[i] == '\'')
			new = ft_join("%f\\'", new);
		else
			new = ft_join("%f%c", new, str[i]);
		i++;
	}
	return (new);
}

int			ft_printenv(char *options)
{
	char	**env;
	int		i;
	char	*str;

	i = 0;
	env = ft_serialize_env(EXPORTED_ONLY);
	while (env[i])
	{
		if (options && options['p'])
			ft_printf("export %s\n", env[i]);
		else
		{
			str = ft_escap(env[i]);
			ft_printf("export %s\n", str);
			free(str);
		}
		free(env[i]);
		i++;
	}
	free(env);
	return (0);
}
