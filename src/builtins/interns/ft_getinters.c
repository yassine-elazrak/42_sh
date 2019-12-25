/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getinters.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sid-bell <sid-bell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/05 01:04:33 by sid-bell          #+#    #+#             */
/*   Updated: 2019/12/20 18:41:46 by sid-bell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	ft_addintern(char *str, int type)
{
	char	*key;
	char	*value;
	t_map	*map;

	ft_get_kv(str, &key, &value);
	map = ft_addtohashmap(key, value, INTERN);
	if (type == ENV_ENTRY && map)
		map->exported = 1;
	free(key);
	free(value);
}

void	ft_getinterns(t_process *cmd, char type)
{
	char	**assign;
	int		i;

	assign = cmd->ass;
	i = 0;
	while (assign && assign[i])
	{
		ft_addintern(assign[i], type);
		i++;
	}
}
