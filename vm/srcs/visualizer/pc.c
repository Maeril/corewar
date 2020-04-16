/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pc.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hben-yah <hben-yah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/08 13:52:02 by hben-yah          #+#    #+#             */
/*   Updated: 2019/12/22 16:16:49 by hben-yah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	display_move_pc(t_vm *vm, t_proc *p)
{
	if (vm->options & (VM_OP_C | VM_OP_S))
	{
		if (vm->cells[p->prev_pc % MEM_SIZE].reverse > 0)
			--vm->cells[p->prev_pc].reverse;
		++vm->cells[p->pc].reverse;
	}
}

void	display_kill_pc(t_vm *vm, t_proc *p)
{
	if (vm->options & (VM_OP_C | VM_OP_D | VM_OP_S))
	{
		if (vm->cells[p->pc % MEM_SIZE].reverse > 0)
			--vm->cells[p->pc].reverse;
	}
}
