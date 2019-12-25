/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jobcontrol.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sid-bell <sid-bell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/02 16:49:44 by sid-bell          #+#    #+#             */
/*   Updated: 2019/12/22 14:09:50 by sid-bell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef JOBCONTROL_H
# define JOBCONTROL_H
# include <signal.h>
# include <termios.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <stdarg.h>
# include "datatypes.h"
# include "libft.h"
# include "exec.h"

typedef struct stat		t_stat;

t_container				*ft_getset(t_container *container);
void					ft_addjob(t_job *job, t_container *container);
void					ft_init_jobcontrol();
void					ft_resetsignals();
void					ft_deljob(t_job *job, t_container *container);
void					ft_addprocess(t_process *process, pid_t pid);
void					ft_wait(t_job *job, int status);
void					ft_jobs_in_child(t_job *job);
void					ft_init_job(t_job *job);
t_job					*ft_getjob_byindex(int index);
void					ft_sort(t_list *list);
void					ft_sigchld(int sig);
void					ft_deljob(t_job *job, t_container *container);
t_job					*ft_getbypgid(t_list *list, pid_t pgid);
int						ft_isstopped(t_job	*job);
t_job					*ft_getjob(char *arg, char *caller);
void					ft_free_job(t_job *job);
void					ft_reset2(int all);
char					*ft_join(char *f, ...);
void					ft_notify(void);
void					ft_init_wait(void);
t_process				*ft_findjob(int pid);
t_process				*ft_getproc_byjob(t_job *job, pid_t pid);
char					*ft_strsignal(int sig);
char					ft_print_termsig(int status);
void					ft_change_state(t_job *job, pid_t pid, int status);
int						ft_stoped(t_job *job);
int						ft_terminated(t_job *job);
void					ft_resetstatus(t_job *job);
void					ft_check_jobs_status(t_job *current);
void					ft_set_last_rvalue(uint8_t rvalue);
uint8_t					ft_get_last_rvalue(void);
void					ft_init_proc(t_process *proc);
uint8_t					ft_getjobstatus(t_process *pr);
void					ft_ignore_signlas(void);
t_job					*ft_pid_lookup(pid_t pid, t_process **procc);
void					ft_free_array(char **args);
t_job					*ft_newjob(pid_t pid, int flag);
t_job					*ft_cpyjob(t_job *job);
void					ft_joingroup(t_params *params, t_process *process);
#endif
