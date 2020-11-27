/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_job_list.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoyassin <yoyassin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/21 18:46:41 by yoyassin          #+#    #+#             */
/*   Updated: 2019/12/20 18:15:36 by yoyassin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static void	*get_node(char *cmd, int bg, int *j, int *old_j)
{
	char	*token;
	void	*curr;

	curr = NULL;
	token = skip_operators(bg ? 2 : 1, cmd, old_j, j);
	if (is_not_blank(token, 0, ft_strlen(token)))
	{
		if (!get_list_node(bg ? 2 : 1, (void *)&curr, token))
		{
			free(token);
			return ((void *)-1);
		}
		if (token)
			free(token);
	}
	return (curr);
}

t_job		*build_jobs_lst(void **head, void **tail, char *cmd, int bg)
{
	t_job	*curr;
	int		old_j;
	int		j;

	curr = NULL;
	j = 0;
	old_j = 0;
	while (cmd[j])
	{
		if (curr && (cmd[j] == BG || (!bg && (cmd[j] == AND || cmd[j] == OR))))
		{
			old_j += j - old_j;
			j += set_flag((void *)curr, cmd[j], 2);
			bg -= bg ? 1 : 0;
			APPEND(1);
			curr = NULL;
		}
		else
		{
			if ((curr = get_node(cmd, bg, &j, &old_j)) == (void *)-1)
				return ((t_job *)-1);
		}
	}
	return (curr);
}

/*
** -free jobs.
*/

t_job		*get_jobs(char **cmd_chain, int bg)
{
	t_job	*head;
	t_job	*curr;
	t_job	*tail;

	curr = NULL;
	head = NULL;
	tail = NULL;
	while (*cmd_chain)
	{
		if (is_not_blank(*cmd_chain, 0, ft_strlen(*cmd_chain)))
		{
			if ((curr = build_jobs_lst((void *)&head,
			(void *)&tail, *cmd_chain, bg)) == (t_job *)-1)
			{
				ft_free_job(head);
				return (NULL);
			}
			append_lst((void *)&head, (void *)&curr, (void *)&tail, 1);
		}
		cmd_chain++;
	}
	return (head);
}
