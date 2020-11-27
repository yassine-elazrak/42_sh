/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansions.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoyassin <yoyassin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/18 20:48:11 by yoyassin          #+#    #+#             */
/*   Updated: 2019/12/24 10:07:38 by yoyassin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

/*
** - Expand all if argument is not quoted.
** - Expand only environment variables if double quoted.
** - No expansions if argument is single quoted.
*/

void			free_arg_list(t_arg **h)
{
	t_arg	*next;

	while (*h)
	{
		next = (*h)->next;
		free((*h)->arg);
		free(*h);
		*h = NULL;
		*h = next;
	}
}

static t_arg	*get_node(void)
{
	t_arg	*c;

	c = NULL;
	if (!(c = malloc(sizeof(t_arg))))
		exit(EXIT_FAILURE);
	c->next = NULL;
	c->arg = NULL;
	return (c);
}

static void		append(t_arg **h, t_arg **c, t_arg **t)
{
	if (!*h)
		*h = *c;
	else
		(*t)->next = *c;
	*t = *c;
}

int				expand_and_append(t_arg **h, t_arg **t, char ***args)
{
	int		size;
	t_arg	*c;

	size = 0;
	c = get_node();
	size = expand(*args, c);
	if (!*h)
		*h = c;
	else
		(*t)->next = c;
	*t = c;
	return (size);
}

void			apply_expansions(t_process *process)
{
	int		size;
	t_arg	*h;
	t_arg	*c;
	t_arg	*t;
	char	**args;

	size = 0;
	h = NULL;
	c = NULL;
	t = NULL;
	args = process->holder;
	process->ass = get_assignments(&args);
	while (args && *args)
	{
		quotes_delimiter(args);
		c = get_node();
		size += expand(args, c);
		append(&h, &c, &t);
		args++;
	}
	ft_free_array(process->holder);
	process->holder = NULL;
	if (size)
		process->arg = convert_args(h, size);
}
