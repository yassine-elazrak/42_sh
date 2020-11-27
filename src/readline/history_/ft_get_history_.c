/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_history_.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sid-bell <sid-bell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/20 08:16:33 by yelazrak          #+#    #+#             */
/*   Updated: 2019/12/25 16:06:39 by sid-bell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static void		ft_del_history(t_init *init)
{
	t_history	*tmp;

	if (!(init->last_history))
		return ;
	tmp = init->last_history->next;
	if (tmp)
	{
		ft_strdel(&tmp->str);
		ft_memdel((void **)&tmp);
	}
	init->last_history->next = NULL;
	init->history_postoin = NULL;
}

static void		ft_update_history(t_init *init, char *line)
{
	t_history	*new;

	new = NULL;
	if (!(init->last_history))
		return ;
	if (!(new = (t_history *)malloc(sizeof(t_history))))
		return ;
	ft_del_history(init);
	new->next = NULL;
	new->prvet = init->last_history;
	new->str = ft_strdup(line);
	init->last_history->next = new;
}

void			ft_add_history_(t_init *init, char *line, int i)
{
	if (i)
	{
		if (ft_strcmp(line, ""))
		{
			ft_del_history(init);
			ft_new_history_(init, line);
			ft_write_file(init);
		}
	}
	else
		ft_update_history(init, line);
}

void			ft_read_file_(t_init *init)
{
	int			fd;
	char		*line;
	char		*name;

	line = NULL;
	name = ft_join("/Users/%s/.history", ft_getusername());
	if (0 > (fd = open(name, O_CREAT | O_RDWR | O_APPEND, 0777)))
	{
		free(name);
		return ;
	}
	free(name);
	while (get_next_line(fd, -1, &line))
	{
		ft_new_history_(init, line);
		ft_strdel(&line);
	}
	close(fd);
}

void			ft_write_file(t_init *init)
{
	int				fd;
	char			c;
	char			*name;

	c = -3;
	name = ft_join("/Users/%s/.history", ft_getusername());
	if (0 > (fd = open(name, O_CREAT | O_RDWR | O_APPEND, 0777)))
	{
		free(name);
		return ;
	}
	free(name);
	if ((init->last_history)->str && ft_strcmp((init->last_history)->str, ""))
	{
		ft_printf_fd(fd, "%f", ft_itoa(init->index, 10));
		write(fd, &c, 1);
		write(fd, (init->last_history)->str,
		ft_promptlen((init->last_history)->str));
		c = -1;
		write(fd, &c, 1);
	}
	close(fd);
}
