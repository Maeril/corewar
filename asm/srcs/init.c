/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myener <myener@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/24 19:08:29 by myener            #+#    #+#             */
/*   Updated: 2020/04/25 22:50:01 by myener           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/asm.h"

void	asm_header_init(header_t *header)
{
	// header->comment = NULL;
	header->magic = COREWAR_EXEC_MAGIC;
	// header->prog_name = NULL;
	header->prog_size = 0;
}

void	asm_struct_tab_init(t_line *line)
{
	line->label = NULL;
	line->instruc = NULL;
	line->param1 = NULL;
	line->param2 = NULL;
	line->param3 = NULL;
	line->nb_param = 0;
	line->param1_sz = 0;
	line->param2_sz = 0;
	line->param3_sz = 0;
	line->line_cor_ln = 0;
	line->called_label = NULL;
	line->relative_cor_addr = 0;
}

void	asm_tools_init(t_tools *tools)
{
	tools->name_filled = 0;
	tools->com_filled = 0;
}