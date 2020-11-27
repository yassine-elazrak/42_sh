/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_autocomplete.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oherba <oherba@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/25 17:05:25 by oherba            #+#    #+#             */
/*   Updated: 2019/12/25 17:12:29 by oherba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	ft_free_auto_lst(t_auto **lst)
{
	if ((*lst))
	{
		if ((*lst)->next)
			ft_free_auto_lst(&(*lst)->next);
		ft_strdel(&((*lst)->str));
		free(*lst);
		*lst = NULL;
	}
}

int		ft_free_return(char **to_complete, int ret)
{
	if (get_shell_cfg(0)->init->to_complete != (*to_complete))
		free(*to_complete);
	return (ret);
}

int		ft_free_return_2(char **tmp, char *to_complete, int ret)
{
	if ((*tmp) != to_complete)
		free(*tmp);
	return (ret);
}

int		ft_cursor_position(char *s, int cursor)
{
	int	start;
	int	end;

	start = 0;
	end = 0;
	while (ft_isspace(*s))
	{
		start++;
		s++;
	}
	end = start;
	while (*s && !ft_isspace(*s))
	{
		end++;
		s++;
	}
	if (cursor >= start && cursor <= end)
		return (1);
	return (0);
}

int		ft_char_exist(t_auto *lst, int i, char *min_completion)
{
	int	n;

	n = 0;
	while (lst)
	{
		if (lst->str[i] != min_completion[i])
			return (0);
		lst = lst->next;
	}
	return (1);
}
