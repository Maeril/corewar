/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   field.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hben-yah <hben-yah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/07 16:15:08 by hben-yah          #+#    #+#             */
/*   Updated: 2019/12/22 18:15:47 by hben-yah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

static void		display_cell(t_vm *vm, int pc, int color)
{
	wattron(vm->display.wfield, color);
	mvwprintw(vm->display.wfield,
		1 + (pc / vm->display.el_per_line),
		2 + ((pc % vm->display.el_per_line) * 3),
		"%02x", vm->field[pc]);
	wattroff(vm->display.wfield, color);
}

void	display_field(t_vm *vm)
{
	int		pc;
	int		color;

	if (vm->options & VM_OP_C)
	{
		pc = 0;
		werase(vm->display.wfield);
		box(vm->display.wfield, ACS_VLINE, ACS_HLINE);
		mvwprintw(vm->display.wfield, 0, 2, " Champs de bataille ");
		while (pc < MEM_SIZE)
		{
			pc = pc % MEM_SIZE;
			if (vm->cells[pc].color)
			{
				if (vm->cells[pc].live && vm->cells[pc].cycle + 50 > vm->cycle)
					color = COLOR_PAIR(WCOLOR - vm->cells[pc].color - 1) | A_BOLD;
				else
				{
					color = COLOR_PAIR(vm->cells[pc].color)
					| (vm->cells[pc].reverse > 0 ? A_REVERSE : 0);
					if (vm->cells[pc].modified && vm->cells[pc].cycle + 50 > vm->cycle)
						color |= A_BOLD;
				}
			}
			else
				color = COLOR_PAIR(20) | A_BOLD;
			display_cell(vm, pc, color);
			++pc;
		}
	}
}
