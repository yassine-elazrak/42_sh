/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_parse_list.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoyassin <yoyassin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/17 13:19:43 by yoyassin          #+#    #+#             */
/*   Updated: 2019/11/06 20:58:47 by yoyassin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static void	*get_node(char *token, char type, int *j, int *old_j)
{
	char	*str;
	void	*curr;

	if (!(get_list_node(0, &curr,
	(str = skip_operators(type == 1 ? 0 : 3, token, old_j, j)))))
	{
		free(str);
		return ((void *)-1);
	}
	if (str)
		free(str);
	return (curr);
}

void		*build_list(void **head, void **tail, char *token, char type)
{
	int		j;
	int		old_j;
	void	*curr;

	j = 0;
	old_j = 0;
	curr = NULL;
	while (token[j])
	{
		if (curr && ((type == 2 && (token[j] == PIPE || token[j] == AND ||
		token[j] == OR)) || (type == 1 && (token[j] == PIPE))))
		{
			old_j += j - old_j;
			j += SETFLAG(0);
			APPEND(0);
			curr = NULL;
		}
		else
		{
			if ((curr = get_node(token, type, &j, &old_j)) == (void *)-1)
				return ((void *)-1);
		}
	}
	return (curr);
}

t_process	*get_process_list(char *cmd_chain, char type)
{
	t_process		*h;
	t_process		*t;
	void			*c;

	h = NULL;
	t = NULL;
	if ((c = build_list((void *)&h, (void *)&t, cmd_chain, type)) == (void *)-1)
		return (NULL);
	append_lst((void *)&h, &c, (void *)&t, 0);
	return (h);
}
