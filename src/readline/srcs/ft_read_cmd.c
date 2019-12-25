/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_read_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yelazrak <yelazrak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/23 20:15:42 by yelazrak          #+#    #+#             */
/*   Updated: 2019/12/23 18:00:16 by yelazrak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void			ft_read_more(char *buffer, t_init *init, char **t)
{
	char		*tmp;

	init->skip_read = 1;
	tmp = *t;
	if (*t[0] == '\0')
		*t = ft_strdup(buffer);
	else
		*t = ft_strjoin(*t, buffer);
	free(tmp);
}

char			*ft_herd_qout_normal(t_init *init,
char *buffer, char **t)
{
	char		*line;

	line = NULL;
	if (!(buffer[0] == 4 && buffer[1] == '\0') && init->search == 1)
		line = ft_search_(*t, init);
	else if (!(buffer[0] == 4 && buffer[1] == '\0') && init->qoute == 1)
	{
		if ((line = ft_qoute(*t, init)))
			ft_add_history_(init, line, 1);
	}
	else if (!(buffer[0] == 4 && buffer[1] == '\0'))
		line = move_cursor_and_mangemant_fonction(*t, init);
	else if ((buffer[0] == 4 && buffer[1] == '\0') &&
	ft_strcmp(init->promt, init->out_put) == 0)
		return (ft_strdup(buffer));
	ft_strdel(t);
	return (line);
}

char			*ft_read(char *buffer, int position, t_init *init)
{
	static char	*t;
	char		*tmp;
	char		*line;

	line = NULL;
	if (t == NULL)
		t = ft_strnew(0);
	if (t[0] == '\n')
		t[0] = '\0';
	if (position < 4)
	{
		init->skip_read = 0;
		tmp = t;
		t = ft_strjoin(t, buffer);
		ft_strdel(&tmp);
		if ((line = ft_herd_qout_normal(init, buffer, &t)))
			return (line);
	}
	else
		ft_read_more(buffer, init, &t);
	return (NULL);
}
