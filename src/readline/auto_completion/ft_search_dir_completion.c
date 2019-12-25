/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_search_dir_completion.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oherba <oherba@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/24 16:00:59 by oherba            #+#    #+#             */
/*   Updated: 2019/12/25 17:14:09 by oherba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	ft_one_dir_completion(t_init *init, char *path, char *tilda)
{
	char	*tmp;

	tmp = NULL;
	tmp = init->completion_lst->str;
	if (tilda)
		init->completion_lst->str =
		ft_strjoin(tilda, init->completion_lst->str);
	else
		init->completion_lst->str = ft_strjoin(path, init->completion_lst->str);
	free(tmp);
}

int		ft_max_len_lst_42(t_auto *lst, int *lst_len)
{
	int		i;
	size_t	max;

	max = 0;
	i = 0;
	*lst_len = 0;
	while (lst)
	{
		if (ft_strlen(lst->str) > max)
			max = ft_strlen(lst->str);
		lst = lst->next;
		(*lst_len)++;
	}
	return (max);
}

t_auto	*ft_search_complete_dir_42(char *to_complete, char *directory)
{
	DIR				*dir;
	struct dirent	*lst;
	t_auto			*auto_lst;
	char			*name;

	auto_lst = NULL;
	if (!(dir = opendir(directory)))
		return (NULL);
	while ((lst = readdir(dir)))
	{
		name = lst->d_name;
		if ((*to_complete != '.' && *name == '.') ||
		ft_strequ("..", name) || ft_strequ(".", name))
			continue;
		if (ft_strncmp(lst->d_name, to_complete, ft_strlen(to_complete)) == 0)
			auto_lst = add_to_auto_42(auto_lst, lst->d_name);
	}
	closedir(dir);
	return (auto_lst);
}

void	ft_is_direct_path_dir(char *to_complete,
	t_init *init, char *path, char *tilda)
{
	char	*tmp;
	int		i;

	tmp = NULL;
	i = ft_strlen(to_complete);
	if (to_complete[i - 1] != '/')
	{
		tmp = ft_strjoin(to_complete, "/");
		init->completion_lst = add_to_auto_42(init->completion_lst, tmp);
		ft_strdel(&tmp);
	}
	else
	{
		init->completion_lst = ft_search_complete_dir_42("", path);
		if (!(init->completion_lst))
			return ;
		ft_max_len_lst_42(init->completion_lst, &i);
		if (i == 1)
			ft_one_dir_completion(init, path, tilda);
	}
}

void	ft_get_completion_dir_42(t_init *init)
{
	char	*path;
	char	*new_completion;
	int		n;
	int		i;
	char	*tilda;

	path = NULL;
	new_completion = NULL;
	tilda = NULL;
	i = 0;
	n = ft_if_is_dir(init->to_complete, &path, &new_completion, &tilda);
	if (n == 2)
		ft_is_direct_path_dir(init->to_complete, init, path, tilda);
	else if (n == 1)
	{
		init->completion_lst = ft_search_complete_dir_42(new_completion, path);
		ft_max_len_lst_42(init->completion_lst, &i);
		if (i == 1)
			ft_one_dir_completion(init, path, tilda);
	}
	else
		init->completion_lst = NULL;
	ft_strdel(&new_completion);
	ft_strdel(&tilda);
	ft_strdel(&path);
}
