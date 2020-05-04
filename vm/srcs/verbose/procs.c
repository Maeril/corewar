/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   procs.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hben-yah <hben-yah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/20 07:57:39 by hben-yah          #+#    #+#             */
/*   Updated: 2019/12/20 08:56:54 by hben-yah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void		put_kill_pc(t_vm *vm, t_proc *p)
{
	if (vm->options & VM_OP_V)
	{
		if (vm->options & VM_OP_UP_V)
		{
			printer(vm, 0,
				"Le process %d n'a pas donné signe de vie depuis ", p->id);
			printer(vm, 0, "%d cycles (CTD %d)\n",
				vm->cycle - p->last_live, vm->cycle_to_die);
		}
		else
			printer(vm, 0, "Process %d hasn't lived for %d cycles (CTD %d)\n",
			p->id, vm->cycle - p->last_live, vm->cycle_to_die);
	}
}
