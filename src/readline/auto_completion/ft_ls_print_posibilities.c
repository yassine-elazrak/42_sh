/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls_print_posibilities.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oherba <oherba@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/24 16:23:15 by oherba            #+#    #+#             */
/*   Updated: 2019/12/24 19:31:20 by oherba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

char	**ft_convert_lst_to_tab(t_auto *lst, int lst_len)
{
	char	**tabl;
	int		i;

	i = 0;
	tabl = NULL;
	if (!(tabl = (char **)ft_memalloc(sizeof(char *) * (1 + lst_len))))
		return (NULL);
	while (lst)
	{
		tabl[i] = ft_strdup(lst->str);
		lst = lst->next;
		i++;
	}
	return (tabl);
}

void	ft_put_2(char *t, int i)
{
	int	j;

	j = ft_strlen(t);
	ft_putstr(t);
	while (j < i)
	{
		ft_putchar(' ');
		j++;
	}
}

int		ft_8_multipl(int l)
{
	int	i;

	i = 0;
	while (i <= l)
		i += 8;
	return (i);
}

void	ft_print_tab(char **t, int b, int m, int n)
{
	int	i;
	int	j;

	i = 0;
	ft_putchar('\n');
	while (i < b)
	{
		j = i;
		while (j < m)
		{
			ft_put_2(t[j], n);
			j += b;
		}
		if (i < b - 1)
			ft_putchar('\n');
		i++;
	}
}

void	ft_ls_print_42(t_auto *lst, int print_len, int lst_len)
{
	struct winsize	info;
	int				a;
	int				b;
	char			**table;

	if (!(table = ft_convert_lst_to_tab(lst, lst_len)))
		return ;
	ioctl(0, TIOCGWINSZ, &info);
	if (!print_len)
		return ;
	a = info.ws_col / print_len;
	if (!a)
		return ;
	b = lst_len / a;
	if ((lst_len % a) != 0)
		b++;
	ft_print_tab(table, b, lst_len, print_len);
	ft_free_array(table);
}
