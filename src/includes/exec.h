/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sid-bell <sid-bell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/18 15:44:26 by sid-bell          #+#    #+#             */
/*   Updated: 2019/12/24 14:34:41 by sid-bell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H
# include "parser.h"
# include <sys/stat.h>
# include "libft.h"
# include "builtins.h"
# define ENV_ENTRY 1
# define INTERN_ENTRY 2

typedef struct stat	t_stat;

void	ft_init_exec();
int		exec(t_job *tokens);
int		ft_fork(t_params *params,
				t_process *process, t_function *func);
void	ft_restorestd(char stdin, char stdout, char stderr);
int		ft_redirect(t_redir *red);
void	ft_restore(t_params *params);
char	*ft_findfile(char *name, char **error, char add);
char	ft_exec_job(t_params *params, t_process *lst);
char	*getfullpath(char *name);
int		ft_pipe(int *pipefd, t_process *process, int *fd);
int		ft_printheredoc(t_process *process);
int		ft_readfile(t_params *params);
char	*ft_getexecutable(t_process *process, int report);
char	ft_run_in_sub(t_process *p);
t_job	*ft_list(t_process *pr);
void	ft_execbg(t_job *job);
t_list	**ft_cppyvars(void);
int		ft_gettmpvars(t_process *process, t_function *func);
#endif
