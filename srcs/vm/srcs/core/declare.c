/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   declare.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hben-yah <hben-yah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/10 09:17:16 by hben-yah          #+#    #+#             */
/*   Updated: 2020/08/02 14:53:01 by hben-yah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	declare_winner(t_vm *vm)
{
	if (vm->options & VM_OP_C && !vm->display.wfield)
		init_visualizer(vm);
	if (vm->last_live_champ)
	{
		if (vm->options & VM_OP_A)
			printer(vm, 0, "Aff : %s\n", vm->last_live_champ->aff.str);
		if (vm->options & VM_OP_UP_V)
			printer(vm, 1,
				"Le champion %d, \"%s\", a gagné au bout de %d cycles !\n",
				vm->last_live_champ->id, vm->last_live_champ->header.prog_name,
				vm->cycle);
		else
			printer(vm, 1, "Contestant %d, \"%s\", has won !\n",
				vm->last_live_champ->id, vm->last_live_champ->header.prog_name,
				vm->cycle);
	}
	if (vm->options & (VM_OP_D | VM_OP_S) && vm->option_nb)
		dump_memory(vm);
	display_end_loop(vm);
}
