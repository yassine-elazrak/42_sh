/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fc_help.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yelazrak <yelazrak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/22 19:08:24 by yelazrak          #+#    #+#             */
/*   Updated: 2019/12/22 19:29:42 by yelazrak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int					ft_printusage(int c)
{
	if (c)
		ft_printf("42sh: fc: -%c: invalid option\n", -c);
	ft_printf("usage :\n\
	fc [-r] [-e editor] [first [last]]\n\
	fc -l [-nr] [first [last]]\n\
	fc -s [old=new] [first]\n");
	return (1);
}

char				*get_name_randm(void)
{
	struct timeval	tv;
	char			*name;
	char			*tmp;

	gettimeofday(&tv, NULL);
	name = ft_itoa(tv.tv_sec, 10);
	tmp = ft_strjoin("/tmp/", name);
	ft_strdel(&name);
	return (tmp);
}

int					read_file_(char *fille)
{
	int				fd;
	char			*line;
	t_job			*tokens;

	line = NULL;
	if ((fd = open(fille, O_RDONLY)) < 0)
		return (1);
	while (get_next_line(fd, '\n', &line))
	{
		ft_add_history_(get_shell_cfg(0)->init, line, 1);
		if ((tokens = parse(line)))
		{
			exec(tokens);
			ft_free_job(tokens);
		}
		ft_strdel(&line);
	}
	close(fd);
	return (0);
}
