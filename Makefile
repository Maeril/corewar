# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tferrieu <tferrieu@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/07/20 15:37:51 by hben-yah          #+#    #+#              #
#    Updated: 2020/08/02 17:06:04 by tferrieu         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

LFT_DIR		=	srcs/libft
ASM_DIR		=	srcs/asm
VM_DIR		=	srcs/vm

ASM_NAME	=	asm
VM_NAME		=	corewar
NAME		=	$(ASM_NAME) $(VM_NAME)

LFT_NAME	=	libft.a
LFT_FILE	=	$(LFT_DIR)/$(LFT_NAME)

all			:	clibft casm cvm $(NAME)

norm 		:
				@make -C $(LFT_DIR)/ norm
				@make -C $(ASM_DIR)/ norm
				@make -C $(VM_DIR)/ norm

clibft		:
				@make -C $(LFT_DIR)/

casm		:
				@make -C $(ASM_DIR)/

cvm			:
				@make -C $(VM_DIR)/

$(NAME)		: 	$(VM_DIR)/$(VM_NAME) $(ASM_DIR)/$(ASM_NAME)
				@cp $(ASM_DIR)/$(ASM_NAME) $(ASM_NAME)
				@cp $(VM_DIR)/$(VM_NAME) $(VM_NAME)

clean		:
				@make -C $(LFT_DIR)/ clean
				@make -C $(ASM_DIR)/ clean
				@make -C $(VM_DIR)/ clean

fclean		:
				@make -C $(LFT_DIR)/ fclean
				@make -C $(ASM_DIR)/ fclean
				@make -C $(VM_DIR)/ fclean
				@rm -f $(NAME)

re			:	fclean all

.PHONY		:	all norm clibft casm cvm clean fclean re
