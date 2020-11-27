/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fc.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sid-bell <sid-bell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/22 11:56:54 by yelazrak          #+#    #+#             */
/*   Updated: 2019/12/25 16:03:49 by sid-bell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int					ft_open_(char **str, char *options, char **args)
{
	int				fd;
	char			*fille;
	char			*cmd;

	cmd = NULL;
	(*str) = get_name_randm();
	fille = (*str);
	if ((fd = open(fille, O_WRONLY | O_RDONLY | O_CREAT | O_TRUNC, 0777)) < 0)
		return (-1);
	if (args[0] && args[1])
		ft_print___(options, args, fd);
	else
	{
		if ((cmd = get_arg(args[0])))
			ft_printf_fd(fd, "%f", cmd);
		else
		{
			close(fd);
			return (-1);
		}
	}
	return (fd);
}

int					ft_creat_cmd(char *edit, char *options, char **args)
{
	char			*cmd;
	char			*fille;
	int				fd;
	t_job			*tokens;
	int				status;

	cmd = NULL;
	if ((fd = ft_open_(&fille, options, args)) < 0)
		return (1);
	if (!edit && (edit = ft_getvlaue_bykey("FCEDIT", INTERN)))
		edit = ft_strdup(edit);
	cmd = ft_join("%s%s%s", edit, "  ", fille);
	ft_strdel(&edit);
	status = 1;
	if ((tokens = parse(cmd)))
	{
		status = exec(tokens);
		ft_free_job(tokens);
	}
	close(fd);
	if (!status)
		read_file_(fille);
	ft_strdel(&cmd);
	ft_strdel(&fille);
	return (status);
}

static void			ft__ex(int i, char **args, char *options)
{
	char			*cmd;
	char			*edit;
	t_job			*tokens;

	cmd = NULL;
	edit = NULL;
	if (args[i])
		cmd = ft_rep_lace(args[i], args[i + 1]);
	else if (!options['s'])
	{
		ft_creat_cmd(edit, options, args + i);
		return ;
	}
	else
		cmd = get_arg(args[i]);
	if ((tokens = parse(cmd)))
	{
		exec(tokens);
		ft_free_job(tokens);
	}
	ft_strdel(&cmd);
}

static int			ft_exec_(char *options, char **args)
{
	char			*edit;
	int				i;

	i = 0;
	edit = NULL;
	if (options['e'])
	{
		if (args[i])
			edit = ft_strdup(args[i]);
		else
			return (ft_printusage(0));
		i++;
	}
	if (options['s'] || (!options['e'] && !options['l']))
		ft__ex(i, args, options);
	else if (options['l'])
		return (ft_print___(options, args + i, 1));
	else if (options['e'])
		return (ft_creat_cmd(edit, options, args + i));
	return (0);
}

int					ft_fc(char **args)
{
	char			options[127];
	int				index;

	ft_bzero(options, 127);
	if ((index = ft_getopt(args, options, "relns")) < 0)
		return (ft_printusage(index));
	return (ft_exec_(options, args + index));
}
