/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   declare.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hben-yah <hben-yah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/10 09:17:16 by hben-yah          #+#    #+#             */
/*   Updated: 2019/12/22 14:24:03 by hben-yah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	declare_winner(t_vm *vm)
{
	if (vm->options & VM_OP_C && !vm->display.wfield)
		init_visualizer(vm);
	if (!vm->survivor && (vm->survivor = get_champ_max_lives(vm)))
		vm->survivor = vm->last_live_champ;
	if (vm->survivor)
	{
		if (vm->options & VM_OP_A)
			printer(vm, 0, "Aff : %s\n", vm->survivor->aff.str);
		if (vm->options & VM_OP_UP_V)
			printer(vm, 1,
				"Le champion %d, \"%s\", a gagné au bout de %d cycles !\n",
				vm->survivor->id, vm->survivor->header.prog_name, vm->cycle);
		else
			printer(vm, 1, "Contestant %d, \"%s\", has won !\n",
				vm->survivor->id, vm->survivor->header.prog_name, vm->cycle);
	}
	else
	{
		if (vm->options & VM_OP_UP_V)
			printer(vm, 1, "Match nul au bout de %d cycles !\n", vm->cycle);
		else
			printer(vm, 1, "Draw match !\n", vm->cycle);
	}
	if (vm->options & (VM_OP_D | VM_OP_S) && vm->option_nb)
		dump_memory(vm);
	display_end_loop(vm);
}
