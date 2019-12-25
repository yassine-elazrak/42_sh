/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sid-bell <sid-bell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/04 23:47:46 by sid-bell          #+#    #+#             */
/*   Updated: 2019/11/28 09:26:27 by sid-bell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	ft_init_hash(void)
{
	t_list	**l;

	l = malloc(sizeof(t_list *) * COUNT);
	get_shell_cfg(0)->hashmap = l;
	ft_empty(0);
}
