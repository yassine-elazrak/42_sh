# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sid-bell <sid-bell@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/11/18 16:55:55 by sid-bell          #+#    #+#              #
#    Updated: 2019/12/22 13:54:39 by sid-bell         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME=libexec.a

OBJ=\
ft_exec.o\
ft_execbg.o\
exec/ft_readfile.o\
exec/ft_pipe.o\
exec/ft_findfile.o\
exec/ft_newexec.o\
exec/ft_redirect.o\
exec/ft_restorestd.o\
exec/ft_run.o\
jobcontrol/ft_addjob.o          jobcontrol/ft_deljob.o          jobcontrol/ft_rvalue.o          jobcontrol/ft_wait.o\
jobcontrol/ft_fg.o              jobcontrol/ft_signals.o         jobcontrol/ft_getjobstatus.o    jobcontrol/init.o\
jobcontrol/ft_bg.o              jobcontrol/ft_free.o            jobcontrol/ft_notify.o          jobcontrol/ft_strsignal.o\
jobcontrol/job_builtins.o		jobcontrol/ft_changestate.o     jobcontrol/ft_jobs.o            jobcontrol/ft_proccess.o\
jobcontrol/ft_tools.o			jobcontrol/signal.o				jobcontrol/ft_cpyjob.o			jobcontrol/ft_joingroup.o

CFLAGS=-Wall -Wextra -Werror -I../includes

all:$(NAME)

$(NAME):$(OBJ)
	@echo "\tCompiling $(NAME)"
	ar rc $(NAME) $(OBJ)

clean:
	rm -rf $(OBJ)

fclean:
	rm -rf $(NAME) $(OBJ)

re:fclean all
