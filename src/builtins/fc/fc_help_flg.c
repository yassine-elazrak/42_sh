/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fc_help_flg.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yelazrak <yelazrak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/22 19:15:50 by yelazrak          #+#    #+#             */
/*   Updated: 2019/12/22 19:17:49 by yelazrak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static void			ft_put_str(char *options, int index, char *str, int fd)
{
	if (options['e'] && !options['l'])
		ft_putendl_fd(str, fd);
	else if (!options['n'])
		ft_printf("%d\t%s\n", index, str);
	else
		ft_printf("\t%s\n", str);
}

static int			ft_print_r(char *options, char **args, int fd)
{
	t_history		*lst;
	int				s;
	int				e;

	lst = get_shell_cfg(0)->init->last_history;
	if (get_start_end(&s, &e, args) < 0)
		return (1);
	while (lst)
	{
		if (lst->index == e)
			break ;
		lst = lst->prvet;
	}
	while (lst && lst->next)
	{
		ft_put_str(options, lst->index, lst->str, fd);
		if (lst->index == s)
			return (0);
		lst = lst->prvet;
	}
	return (0);
}

int					ft_print___(char *options, char **args, int fd)
{
	t_history		*lst;
	int				s;
	int				e;

	if (options['r'])
		return (ft_print_r(options, args, fd));
	lst = get_shell_cfg(0)->init->last_history;
	if (get_start_end(&s, &e, args) < 0)
		return (1);
	while (lst)
	{
		if (lst->index == s)
			break ;
		lst = lst->prvet;
	}
	while (lst && lst->next)
	{
		ft_put_str(options, lst->index, lst->str, fd);
		if (lst->index == e)
			return (0);
		lst = lst->next;
	}
	return (0);
}

static char			*get_index(int i)
{
	t_history		*tmp;

	tmp = get_shell_cfg(0)->init->last_history;
	while (tmp)
	{
		if (tmp->index == i)
			return (ft_strdup(tmp->str));
		tmp = tmp->prvet;
	}
	return (NULL);
}

char				*get_arg(char *key)
{
	t_history		*lst;
	char			*cmd;

	cmd = NULL;
	if (key && ft_isdigit(key[0]))
	{
		if ((cmd = get_index(ft_atoi((const char *)key))))
			return (cmd);
		else
			return (ft_strdup(get_shell_cfg(0)->init->last_history->str));
	}
	lst = get_shell_cfg(0)->init->last_history;
	if (key == NULL)
		return (ft_strdup(lst->str));
	if (ft_isdigit(key[0]))
		return (get_index(ft_atoi(key)));
	while (lst)
	{
		if (ft_strncmp(lst->str, key, ft_strlen(key)) == 0)
			return (ft_strdup(lst->str));
		lst = lst->prvet;
	}
	return (ft_strdup(get_shell_cfg(0)->init->last_history->str));
}
