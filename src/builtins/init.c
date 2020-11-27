/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sid-bell <sid-bell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/28 12:12:08 by sid-bell          #+#    #+#             */
/*   Updated: 2019/12/24 13:44:11 by sid-bell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

t_shell	*get_shell_cfg(t_shell *new)
{
	static t_shell	*sh;

	if (new)
		sh = new;
	return (sh);
}

char	*ft_getusername(void)
{
	return (getlogin());
}

void	init_(t_shell *shell, char **env, t_init *init)
{
	get_shell_cfg(shell);
	shell->tmpvars = NULL;
	shell->interractive = 1;
	ft_init_exec();
	ft_init_builtins(env);
	ft_init_readline(init);
	ft_read_file_(init);
	ft_addtohashmap("FCEDIT", "vim", INTERN);
	ft_addtohashmap("?", "0", INTERN);
	if (!ft_getbykey("PWD", INTERN))
		ft_addtohashmap("PWD", getcwd(0, 0), INTERN);
	shell->init = init;
	shell->pwd = ft_strdup(ft_getenv("PWD"));
	shell->last_exit = 0;
	shell->subshell = 0;
	shell->abort = 0;
	shell->newmaps = NULL;
}
