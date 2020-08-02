/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hben-yah <hben-yah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/18 07:12:23 by hben-yah          #+#    #+#             */
/*   Updated: 2019/12/22 11:12:36 by hben-yah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	put_move(t_vm *vm, t_proc *p)
{
	int		len;
	int		i;

	len = p->pc - p->prev_pc;
	if (len < 0)
		len += MEM_SIZE;
	if (vm->options & VM_OP_UP_V)
	{
		printer(vm, 0, "    Déplacement de %d : ", len);
		print_coords(vm, 0, p->prev_pc);
		printer(vm, 0, " --> ");
		print_coords(vm, 0, p->pc);
		printer(vm, 0, " : ");
	}
	else
		printer(vm, 0, "ADV %d (0x%04x -> 0x%04x) ", len,
			p->prev_pc, p->prev_pc + len);
	i = 0;
	while (i < len)
		printer(vm, 0, "%02x ", vm->field[(p->prev_pc + i++) % MEM_SIZE]);
	printer(vm, 0, "\n");
}
