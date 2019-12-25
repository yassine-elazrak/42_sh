/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sid-bell <sid-bell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/18 15:40:36 by sid-bell          #+#    #+#             */
/*   Updated: 2019/12/23 18:23:47 by sid-bell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHELL_H
# define SHELL_H
# include <fcntl.h>
# include <stdint.h>
# include "autocomplete.h"
# include "datatypes.h"
# include "readline.h"
# include "parser.h"
# include "exec.h"
# include "libft.h"
# include "builtins.h"
# include "jobcontrol.h"
# include <utmpx.h>
# include <sys/mman.h>
# include <fcntl.h>
# include <sys/stat.h>
# include <unistd.h>
# define EXIT_ON_EOT 0
# define RETURN_ON_EOT 1

char		*ft_getusername(void);
t_shell		*get_shell_cfg(t_shell *new);
void		init_(t_shell *shell, char **env, t_init *init);
char		*ft_getprompt();
int			ft_promptlen(char *prompt);
#endif
