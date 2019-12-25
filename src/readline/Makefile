# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: oherba <oherba@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/11/18 16:55:55 by sid-bell          #+#    #+#              #
#    Updated: 2019/12/25 17:07:56 by oherba           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME=libreadline.a

OBJ= srcs/ft_put.o                 termcap/ft_herdoc_exec.o\
srcs/ft_read_cmd.o\
srcs/ft_select_copy_paste.o   termcap/ft_mul_line.o\
srcs/ft_select_copy_paste_2.o termcap/ft_qout.o\
srcs/moves_2.o                termcap/ft_treat_line.o\
srcs/moves_3.o                termcap/move_cursor_of_line.o\
srcs/read_line_.o             termcap/print_line.o\
termcap/cursor_moves.o        termcap/take_line.o\
history_/ft_get_history_.o 	   history_/search_.o\
auto_completion/ft_autocomplete.o auto_completion/ft_take_to_complete.o\
auto_completion/ft_is_first_cmd.o auto_completion/ft_check_if_dir.o\
auto_completion/ft_path_builtin_completion.o\
auto_completion/ft_search_completion.o\
auto_completion/ft_search_dir_completion.o\
auto_completion/ft_replace_completion.o\
auto_completion/ft_ls_print_posibilities.o\
auto_completion/ft_max_completion.o\
auto_completion/ft_free_autocomplete.o\
termcap/help_string.o\
termcap/help_string_2.o       history_/history.o\

CFLAGS= -Wall -Wextra -Werror -I../includes

all:$(NAME)

$(NAME):$(OBJ)
	@echo "\tCompiling $(NAME)"
	ar rc $(NAME) $(OBJ)

clean:
	rm -rf $(OBJ)

fclean:
	rm -rf $(NAME) $(OBJ)

re:fclean all