/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hben-yah <hben-yah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/05 17:44:06 by hben-yah          #+#    #+#             */
/*   Updated: 2020/08/02 14:56:12 by hben-yah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void		init_vm(t_vm *vm)
{
	ft_bzero(vm, sizeof(t_vm));
	vm->cycle_to_die = CYCLE_TO_DIE;
}

void		init_proc(t_vm *vm, t_champ *champ, size_t pc)
{
	t_proc	*proc;

	if (!(proc = (t_proc*)ft_memalloc(sizeof(t_proc))))
		exit_vm(vm, "malloc error : init proc", 1);
	proc->id = ++vm->id_procs;
	proc->number = champ->number;
	set_reg_val(proc, 1, champ->number);
	proc->pc = pc;
	proc->prev_pc = pc;
	proc->champ = champ;
	proc->next = vm->proc;
	ft_memcpy(vm->field + pc, champ->prog, champ->header.prog_size);
	display_color(vm, proc, pc, champ->header.prog_size);
	display_move_pc(vm, proc);
	vm->proc = proc;
	++vm->n_procs;
	++champ->n_procs;
	put_champion(vm, champ);
}

void		init_procs(t_vm *vm)
{
	t_champ		*champ;
	size_t		gap;
	size_t		pc;

	put_contestants(vm);
	gap = MEM_SIZE / vm->n_champs;
	pc = 0;
	champ = vm->champ;
	while (champ)
	{
		init_proc(vm, champ, pc);
		pc += gap;
		vm->last_live_champ = champ;
		champ = champ->next;
	}
	display_refresh(vm);
}
