/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myener <myener@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/24 19:08:29 by myener            #+#    #+#             */
/*   Updated: 2020/05/13 02:47:50 by myener           ###   ########.fr       */
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

void	asm_struct_tab_init(line_t *line, int len)
{
	int i;

	i = 0;
	while (i < len)
	{
		line[i].label = NULL;
		line[i].instruc = NULL;
		line[i].param1 = NULL;
		line[i].param2 = NULL;
		line[i].param3 = NULL;
		line[i].nb_param = 0;
		line[i].param1_sz = 0;
		line[i].param2_sz = 0;
		line[i].param3_sz = 0;
		line[i].line_cor_ln = 0;
		line[i].called_label = NULL;
		line[i].relative_cor_addr = 0;
		i++;
	}
}

void	asm_tools_init(tools_t *tools)
{
	tools->name_filled = 0;
	tools->com_filled = 0;
	tools->cor_line_counter = 0;
	tools->prog_size = 0;
}