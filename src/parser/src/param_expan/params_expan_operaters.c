/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   params_expan_operaters.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmostafa <mmostafa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/03 17:11:08 by mmostafa          #+#    #+#             */
/*   Updated: 2019/12/24 11:57:08 by mmostafa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

char	*plus_func(t_param_expan_st *p_w)
{
	if (p_w->type == 'P')
	{
		p_w->map = ft_getbykey(p_w->param, INTERN);
		if (p_w->map && ft_strlen(p_w->map->value))
			return (ft_strdup(p_w->word));
		else if ((p_w->map && !ft_strlen(p_w->map->value)) || !p_w->map)
			return (ft_strdup(""));
	}
	p_w->map = ft_getbykey(p_w->param, INTERN);
	if (p_w->map)
		return (ft_strdup(p_w->word));
	return (ft_strdup(""));
}

char	*min_func(t_param_expan_st *p_w)
{
	if (p_w->type == 'P')
	{
		p_w->map = ft_getbykey(p_w->param, INTERN);
		if (p_w->map && ft_strlen(p_w->map->value))
			return (ft_strdup(p_w->map->value));
		if ((p_w->map && !ft_strlen(p_w->map->value)) || !p_w->map)
			return (ft_strdup(p_w->word));
	}
	p_w->map = ft_getbykey(p_w->param, INTERN);
	if (!p_w->map)
		return (ft_strdup(p_w->word));
	if (p_w->map && ft_strlen(p_w->map->value))
		return (ft_strdup(p_w->map->value));
	return (ft_strdup(""));
}

char	*assign_func(t_param_expan_st *p_w)
{
	if (p_w->type == 'P')
	{
		p_w->map = ft_getbykey(p_w->param, INTERN);
		if (p_w->map && ft_strlen(p_w->map->value))
			return (ft_strdup(p_w->map->value));
		if ((p_w->map && !ft_strlen(p_w->map->value)) || !p_w->map)
		{
			ft_addtohashmap(p_w->param, p_w->word, INTERN);
			return (ft_strdup(p_w->word));
		}
	}
	p_w->map = ft_getbykey(p_w->param, INTERN);
	if (p_w->map && ft_strlen(p_w->map->value))
		return (ft_strdup(p_w->map->value));
	if ((p_w->map && !ft_strlen(p_w->map->value)))
		return (ft_strdup(""));
	ft_addtohashmap(p_w->param, p_w->word, INTERN);
	return (ft_strdup(p_w->word));
}

char	*error_func(t_param_expan_st *p_w)
{
	if (p_w->type == 'P')
	{
		p_w->map = ft_getbykey(p_w->param, INTERN);
		if (p_w->map && ft_strlen(p_w->map->value))
			return (ft_strdup(p_w->map->value));
		if ((p_w->map && !ft_strlen(p_w->map->value)) || !p_w->map)
		{
			ft_putstr_fd("42sh: ", 2);
			ft_putstr_fd(p_w->param, 2);
			ft_putstr_fd(": ", 2);
			ft_putendl_fd(p_w->word, 2);
			return (NULL);
		}
	}
	p_w->map = ft_getbykey(p_w->param, INTERN);
	if (p_w->map && ft_strlen(p_w->map->value))
		return (ft_strdup(p_w->map->value));
	if ((p_w->map && !ft_strlen(p_w->map->value)))
		return (ft_strdup(""));
	ft_putstr_fd("42sh: ", 2);
	ft_putstr_fd(p_w->param, 2);
	ft_putstr_fd(": ", 2);
	ft_putendl_fd(p_w->word, 2);
	return (NULL);
}

char	*operators_manager(t_param_expan_st *p_w)
{
	if (p_w->type == 'P' || p_w->type == 'A')
	{
		if (p_w->operation_type == '+')
			return (plus_func(p_w));
		if (p_w->operation_type == '-')
			return (min_func(p_w));
		if (p_w->operation_type == '=')
			return (assign_func(p_w));
		if (p_w->operation_type == '?')
			return (error_func(p_w));
	}
	if (p_w->type == 'F')
		return (rm_ffixers(p_w));
	return ((p_w->map = ft_getbykey(p_w->param, 1)) ?
	ft_strdup(p_w->map->value) : ft_strdup(""));
}
