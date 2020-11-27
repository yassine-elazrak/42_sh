/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yelazrak <yelazrak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/25 20:30:26 by yelazrak          #+#    #+#             */
/*   Updated: 2019/12/25 20:33:01 by yelazrak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static char			*ft_join__(char *str, char *new, int index, int j)
{
	char			*tmp;
	char			*line;
	char			*tmp_2;

	tmp = NULL;
	line = NULL;
	tmp_2 = NULL;
	tmp = ft_strdup(&str[j]);
	line = ft_strsub(str, 0, index);
	tmp_2 = ft_strjoin(line, new);
	ft_strdel(&new);
	ft_strdel(&line);
	line = ft_strjoin(tmp_2, tmp);
	ft_strdel(&tmp_2);
	ft_strdel(&tmp);
	return (line);
}

char				*ft_expansion(t_init *init, char *str)
{
	char			*tmp;
	char			*new;
	int				i;
	int				j;

	i = -1;
	while (str[++i])
	{
		if (str[i] == '!' && str[i + 1] &&
		str[i + 1] != ' ' && str[i + 1] != '\t')
		{
			j = get_(&str[i + 1]);
			tmp = ft_strsub(str, i + 1, j);
			if (!(new = ft_get_data(init, tmp)))
			{
				ft_strdel(&tmp);
				return (NULL);
			}
			ft_strdel(&tmp);
			tmp = str;
			str = ft_join__(str, new, i, i + j + 1);
			ft_strdel(&tmp);
		}
	}
	return (str);
}

int					get_(char *str)
{
	int				a;
	int				i;

	i = 0;
	if (str[i] == '-')
		i++;
	if (str[i] == '!')
		return (1);
	a = ft_isdigit(str[i]);
	while (str[i] && str[i] != ' ' && str[i] != '\t' && str[i] != '\n')
	{
		if (a == 1 && ft_isdigit(str[i]) == 0)
			return (i);
		if (a == 0 && ft_isdigit(str[i]) == 1)
			return (i);
		i++;
	}
	return (i);
}

static void			ft_new_help(t_init *init, char *line, t_history **tmp)
{
	t_history		*new;

	new = NULL;
	(void)line;
	new = *tmp;
	new->prvet = init->last_history;
	(init->last_history)->next = new;
	init->last_history = new;
	if (init->history_postoin)
		init->history_postoin = new;
}

void				ft_new_history_(t_init *init, char *line)
{
	t_history		*new;

	new = NULL;
	init->index++;
	if (!(new = (t_history *)malloc(sizeof(t_history))))
		return ;
	if (ft_strchr(line, -3))
	{
		new->str = ft_strdup(ft_strchr(line, -3) + 1);
		new->index = ft_atoi(line);
	}
	else
	{
		new->str = ft_strdup(line);
		new->index = init->index;
	}
	new->next = NULL;
	new->prvet = NULL;
	if (!init->history)
	{
		init->last_history = new;
		init->history = new;
		return ;
	}
	ft_new_help(init, line, &new);
}
