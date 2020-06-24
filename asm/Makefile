# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: myener <myener@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/04/11 18:16:32 by myener            #+#    #+#              #
#    Updated: 2020/06/23 21:39:44 by myener           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = asm

SRCDIR	:=	./srcs
OBJDIR	:=	./objs

SRCS_NAME =		cleaner.c			\
				error_output.c		\
				fill_tab_sizes.c	\
				fill_tab_input.c	\
				header_fill.c		\
				init_free_tools.c	\
				instruct_tools.c	\
				main.c				\
				struct_tab_fill.c	\
				tools.c				\
				write_to_file.c		\

FLAGS =	 -g3 -Wall -Wextra -Werror -I srcs/libft/includes

OBJS	:=	$(addprefix $(OBJDIR)/,$(SRCS_NAME:.c=.o))
SRCS	:=	$(addprefix $(SRCDIR)/,$(SRCS_NAME))

LIBFT = srcs/libft/libft.a

all: libft $(NAME)

$(NAME): $(LIBFT) $(OBJS) srcs/includes/asm.h
	@printf "\e[36m Creating: \e[32m$(NAME)\e[0m\n"
	@clang $(OBJS) $(LIBFT) -o $(NAME)

libft:
	@make -C srcs/libft

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@printf "\e[34m Compiling: \e[0m$< -> $@\n"
	@mkdir -p $(dir $@)
	@clang $(FLAGS) -c $< -o $@

clean:
	@printf "\e[34m Cleaning asm:	\e[0m$(OBJDIR)\e[0m\n"
	@rm -f $(OBJ) $@
	@rm -rf $(OBJDIR)
	@make clean -C srcs/libft

fclean: clean
	@printf "\e[36m Removing: \e[0m"
	@printf "\e[32masm \e[0m\n"
	@rm -f $(NAME) $@
	@rm -rf $(LIBFT)

re: fclean all

.PHONY: all, clean, fclean, re