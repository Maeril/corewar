/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hben-yah <hben-yah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/05 17:44:06 by hben-yah          #+#    #+#             */
/*   Updated: 2019/12/21 11:31:25 by hben-yah         ###   ########.fr       */
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
	//proc->name = champ->header.prog_name;
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
	pc = 0;//gap * (vm->n_champs - 1);
	champ = vm->champ;
	while (champ)
	{
		init_proc(vm, champ, pc);
		pc += gap;
		champ = champ->next;
	}
	display_refresh(vm);
}


/*void		init_procs(t_vm *vm)
{
	int		i;
	int		j;
	int		nbr;
	t_proc	*curr;

	create_all_process(vm);
	
	i = 0;
	j = (MEM_SIZE / vm->n_champs) * (vm->n_champs - 1);
	nbr = vm->n_champs;
	curr = vm->proc;
	while (++i <= vm->n_champs)
	{
		curr->pc = j;
		curr->prev_pc = j;
		curr->live = 0;
		visu_colorized(vm, curr, get_progsize(vm, nbr--), curr->pc);
		visu_movepc(vm, curr);
		curr = curr->next;
		j -= MEM_SIZE / vm->n_champs;
	}
	display_refresh(vm);
}
*/
