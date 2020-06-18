# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hben-yah <hben-yah@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/04/16 20:26:22 by hben-yah          #+#    #+#              #
#    Updated: 2020/06/18 08:05:11 by hben-yah         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			=	corewar

COMP			=	gcc
FLAG			=	-Wall -Wextra -Werror
FLAGDEV         =   -g3

# Sources paths
FILES_C			=   \
					reader/reader.c \
					tools/carry.c \
					tools/move_pc.c \
					tools/read.c \
					tools/reg.c \
					tools/arg.c \
					tools/write.c \
					core/init.c \
					core/run.c \
					core/exit.c \
					core/declare.c \
					core/main.c \
					core/procs.c \
					operations/or.c \
					operations/zjmp.c \
					operations/lfork.c \
					operations/sti.c \
					operations/fork.c \
					operations/live.c \
					operations/xor.c \
					operations/ldi.c \
					operations/and.c \
					operations/st.c \
					operations/op.c \
					operations/aff.c \
					operations/lld.c \
					operations/lldi.c \
					operations/add.c \
					operations/sub.c \
					operations/ld.c \
					verbose/ctd.c \
					verbose/move.c \
					verbose/op.c \
					verbose/dump.c \
					verbose/printer.c \
					verbose/arg.c \
					verbose/alive.c \
					verbose/procs.c \
					verbose/champions.c \
					structs/del_vm.c \
					structs/del_proc.c \
					structs/insert_proc.c \
					structs/fork_proc.c \
					structs/del_champ.c \
					structs/get_champ.c \
					structs/new_proc.c \
					errors/invalid_file_error.c \
					errors/file_not_found_error.c \
					errors/usage.c \
					errors/number_error.c \
					errors/invalid_option_error.c \
					errors/cycle_arg_error.c \
					errors/champions_error.c \
					arguments/champion.c \
					arguments/handler.c \
					arguments/parser.c \
					arguments/options.c \
					visualizer/colrow.c \
					visualizer/resize.c \
					visualizer/init.c \
					visualizer/info.c \
					visualizer/border.c \
					visualizer/reset.c \
					visualizer/breakdown.c \
					visualizer/refresh.c \
					visualizer/pc.c \
					visualizer/header.c \
					visualizer/winner.c \
					visualizer/end.c \
					visualizer/legend.c \
					visualizer/events.c \
					visualizer/field.c \
					visualizer/key.c \
					visualizer/color.c
FILES_O			=	$(FILES_C:.c=.o)
FILES_H			=	\
					prototypes.h \
					vm.h

#Directories
SRCS_SD			= 	\
					reader \
					tools \
					core \
					operations \
					verbose \
					structs \
					errors \
					arguments \
					visualizer
SRCS_D			=	./srcs/
OBJS_D			=   ./objs/
INCL_D 			=	./includes/

# Paths
SRCS			= 	$(addprefix $(SRCS_D), $(FILES_C))
OBJS			=	$(addprefix $(OBJS_D), $(FILES_O))
INCL			=	$(addprefix $(INCL_D), $(FILES_H))

# Libft
LFT_D			=	../libft/
LFT_P			=	$(addprefix $(LFT_D), libft.a)
LFT_I			=	../libft/includes/
LFT_L			=	../libft
LFT_H			=	\
					ft_prototypes.h \
					libft.h \
					ft_defines.h \
					ft_structs.h \
					ft_printf.h


# Ncurses
CUR				=	-lncurses

# Op
OP_D			=	../shared

# Rules

all				:	$(NAME)

dev				:	debug $(NAME)


$(NAME)			:	$(LFT_P) $(OBJS)
					@echo "\nAssemblage et création de l'exécutable $(NAME)"
					@$(COMP) $(FLAG) $(OBJS) $(LFT_P) $(CUR) -o $(NAME)
					@echo "Terminé"

$(LFT_P)		:	force
					@echo "Vérification de la librairie Libft"
					@make -C $(LFT_D)

$(OBJS_D)%.o	:	$(SRCS_D)%.c $(addprefix $(LFT_I), $(LFT_H)) $(INCL)
					@echo -e "\033[2K\c"
					@echo "\rCréation de l'objet $@\c"
					@mkdir -p $(addprefix $(OBJS_D), $(SRCS_SD))
					@$(COMP) $(FLAG) -I $(LFT_I) -I $(INCL_D) -I $(OP_D) -o $@ -c $<

clean			:
					@make -C $(LFT_D) clean
					@echo "Nettoyage des objets $(OBJS_D)"
					@rm -rf $(OBJS_D)

fclean			:
					@make -C $(LFT_D) fclean
					@echo "Nettoyage des objets $(OBJS_D)"
					@rm -rf $(OBJS_D)
					@echo "Nettoyage de l'exécutable $(NAME)"
					@rm -f $(NAME)

re				:	fclean all

debug			:	force
					@$(eval FLAG = $(FLAG) $(FLAGDEV))

force			:
					@true

.PHONY			:	all clean fclean re force debug dev
