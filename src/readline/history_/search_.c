/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yelazrak <yelazrak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/02 17:55:42 by yelazrak          #+#    #+#             */
/*   Updated: 2019/12/22 18:35:49 by yelazrak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static char			*get_last_arg(t_init *init, char *str)
{
	t_history		*tmp;

	tmp = init->last_history;
	if (ft_strcmp(str, "!") == 0)
	{
		return (ft_strdup(tmp->str));
	}
	while (tmp)
	{
		if (ft_strncmp(tmp->str, str, ft_promptlen(str)) == 0)
			return (ft_strdup(tmp->str));
		tmp = tmp->prvet;
	}
	return (NULL);
}

static char			*get_first_arg(t_init *init, char *str)
{
	t_history		*tmp;

	tmp = init->history;
	while (tmp)
	{
		if (ft_strncmp(tmp->str, str + 1, ft_promptlen(str + 1)) == 0)
			return (ft_strdup(tmp->str));
		tmp = tmp->next;
	}
	return (NULL);
}

static char			*get_history_index(t_init *init, int i)
{
	t_history		*tmp;

	tmp = init->last_history;
	while (tmp)
	{
		if (i == 1)
			return (ft_strdup(tmp->str));
		tmp = tmp->prvet;
		i--;
	}
	return (NULL);
}

static char			*get_index(t_init *init, int i)
{
	t_history		*tmp;

	tmp = init->last_history;
	while (tmp)
	{
		if (tmp->index == i)
			return (ft_strdup(tmp->str));
		tmp = tmp->prvet;
	}
	return (NULL);
}

char				*ft_get_data(t_init *init, char *str)
{
	char			*t;

	t = NULL;
	if (str[0] == '-' && ft_isdigit(str[1]))
	{
		t = get_history_index(init, ft_atoi(&str[1]));
		return (t);
	}
	else if (str[0] == '-' && !ft_isdigit(str[1]))
	{
		t = get_first_arg(init, str);
		ft_putendl(t);
		return (t);
	}
	else if (ft_isdigit(str[0]))
	{
		t = get_index(init, ft_atoi(&str[0]));
		return (t);
	}
	else
		t = get_last_arg(init, str);
	return (t);
}
