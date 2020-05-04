# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hben-yah <hben-yah@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/07/20 15:37:51 by hben-yah          #+#    #+#              #
#    Updated: 2019/11/20 08:04:16 by hben-yah         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

ASM_NAME	=	asm
VM_NAME		=	corewar
NAME		=	$(ASM_NAME) $(VM_NAME)

LFT_NAME	=	libft.a
LFT_FILE	=	$(LFT_DIR)/$(LFT_NAME)

LFT_DIR		=	libft
ASM_DIR		=	asm
VM_DIR		=	vm

all			:	clibft casm cvm $(NAME)

norm 		:
				@make -C $(LFT_DIR)/ norm
				@make -C $(ASM_DIR)/ norm
				@make -C $(VM_DIR)/ norm

clibft		:
				@make -C $(LFT_DIR)/

casm		:
				#@make -C $(ASM_DIR)/

cvm			:
				@make -C $(VM_DIR)/

$(NAME)		: 	$(VM_DIR)/$(VM_NAME) #$(ASM_DIR)/$(ASM_NAME)
				#@cp $(ASM_DIR)/$(ASM_NAME) $(ASM_NAME)
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
