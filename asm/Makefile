# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: myener <myener@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/04/11 18:16:32 by myener            #+#    #+#              #
#    Updated: 2020/04/11 18:17:41 by myener           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = asm

SRCDIR	:=	./srcs
OBJDIR	:=	./objs

SRCS_NAME =

FLAGS =	 -Wall -Wextra -Werror -I srcs/libft

OBJS	:=	$(addprefix $(OBJDIR)/,$(SRCS_NAME:.c=.o))
SRCS	:=	$(addprefix $(SRCDIR)/,$(SRCS_NAME))

LIBFT = srcs/libft/libft.a

all: $(NAME)

$(NAME): $(LIBFT) $(OBJS) srcs/includes/asm.h
	@printf "\e[36m Creating: \e[32m$(NAME)\e[0m\n"
	@gcc $(OBJS) $(LIBFT) -o $(NAME)

$(LIBFT):
	@make -C srcs/libft

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@printf "\e[34m Compiling: \e[0m$< -> $@\n"
	@mkdir -p $(dir $@)
	@gcc $(FLAGS) -c $< -o $@

clean:
	@printf "\e[34m Cleaning asm:	\e[0m$(OBJDIR)\e[0m\n"
	@rm -f $(OBJ) $@
	@rm -rf $(OBJDIR)
	@make clean -C srcs/libft

fclean: clean
	@printf "\e[36m Removing: \e[0m"
	@printf "\e[32masm \e[0m\n"
	@rm -f $(NAME) $@
	@rm -rf srcs/libft/libft.a

re: fclean all

.PHONY: all, clean, fclean, re