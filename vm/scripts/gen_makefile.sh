#!/bin/sh
echo "# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hben-yah <hben-yah@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: \c" > Makefile

date "+%Y/%m/%d %H:%M:%S" | tr -d '\n' >> Makefile

echo " by hben-yah          #+#    #+#              #
#    Updated: \c" >> Makefile

date "+%Y/%m/%d %H:%M:%S" | tr -d '\n' >> Makefile

echo " by hben-yah         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			=	corewar

COMP			=	clang
FLAG			=	-Wall -Wextra -Werror
FLAGDEV         =   -g3

# Sources paths
FILES_C			=   \\" >> Makefile
(cd srcs; find . -name '*.c' | grep -v "old_" | sed -e '$ ! s/$/ \\/' | sed -e 's/^\.\//					/' >> ../Makefile)
echo "FILES_O			=	\$(FILES_C:.c=.o)
FILES_H			=	\\" >> Makefile
(cd includes; find . -name '*.h' | sed -e '$ ! s/$/ \\/' | sed -e 's/^\.\//					/' >> ../Makefile)
echo "
#Directories
SRCS_SD			= 	\\" >> Makefile
(cd srcs; find . ! -path . -type d | sed -e '$ ! s/$/ \\/' | sed -e 's/^\.\//					/' >> ../Makefile)

echo "SRCS_D			=	./srcs/
OBJS_D			=   ./objs/
INCL_D 			=	./includes/

# Paths
SRCS			= 	\$(addprefix \$(SRCS_D), \$(FILES_C))
OBJS			=	\$(addprefix \$(OBJS_D), \$(FILES_O))
INCL			=	\$(addprefix \$(INCL_D), \$(FILES_H))

# Libft
LFT_D			=	../libft/
LFT_P			=	\$(addprefix \$(LFT_D), libft.a)
LFT_I			=	../libft/includes/
LFT_L			=	../libft
LFT_H			=	\\" >> Makefile
find ../libft/includes -name '*.h' -exec basename {} \; | sed -e '$ ! s/$/ \\/' | sed -e 's/^/					/' >> Makefile

echo "

# Ncurses
CUR				=	-lncurses

# Op
OP_D			=	../shared

# Rules

all				:	\$(NAME)

dev				:	debug \$(NAME)


\$(NAME)			:	\$(LFT_P) \$(OBJS)
					@echo \"\\\nAssemblage et création de l'exécutable \$(NAME)\"
					@\$(COMP) \$(FLAG) \$(OBJS) \$(LFT_P) \$(CUR) -o \$(NAME)
					@echo \"Terminé\"

\$(LFT_P)		:	force
					@echo \"Vérification de la librairie Libft\"
					@make -C \$(LFT_D)

\$(OBJS_D)%.o	:	\$(SRCS_D)%.c \$(addprefix \$(LFT_I), \$(LFT_H)) \$(INCL)
					@echo -e \"\\\033[2K\\\c\"
					@echo \"\\\rCréation de l'objet \$@\\\c\"
					@mkdir -p \$(addprefix \$(OBJS_D), \$(SRCS_SD))
					@\$(COMP) \$(FLAG) -I \$(LFT_I) -I \$(INCL_D) -I \$(OP_D) -o \$@ -c \$<

clean			:
					@make -C \$(LFT_D) clean
					@echo \"Nettoyage des objets \$(OBJS_D)\"
					@rm -rf \$(OBJS_D)

fclean			:
					@make -C \$(LFT_D) fclean
					@echo \"Nettoyage des objets \$(OBJS_D)\"
					@rm -rf \$(OBJS_D)
					@echo \"Nettoyage de l'exécutable \$(NAME)\"
					@rm -f \$(NAME)

re				:	fclean all

debug			:	force
					@\$(eval FLAG = \$(FLAG) \$(FLAGDEV))

force			:
					@true

.PHONY			:	all clean fclean re force debug dev" >> Makefile