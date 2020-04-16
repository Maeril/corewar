/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   zjmp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hben-yah <hben-yah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/24 16:52:45 by hben-yah          #+#    #+#             */
/*   Updated: 2019/12/21 11:12:03 by hben-yah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

static void		put_zjmp(t_vm *vm, t_proc *p, t_arg arg)
{
	put_op(vm, p);
	if (vm->options & VM_OP_UP_V)
	{
		printer(vm, 0, "%d\n", arg.index);
		printer(vm, 0, "    carry = %d --> ", p->carry);
		if (p->carry)
		{
			printer(vm, 0, "saut jusqu'à ");
			print_coords(vm, 0, p->pc);
			printer(vm, 0, "\n");
		}
		else
			printer(vm, 0, "sans effet\n");
	}
	else
		printer(vm, 0, "%d %s\n", arg.index, p->carry == 1 ? "OK" : "FAILED");
}

void		operate_zjmp(t_vm *vm, t_proc *p)
{
	t_arg	arg;
	
	ft_bzero(&arg, sizeof(arg));
	arg.type = T_DIR;
	read_arg(vm, p, &arg);
	if (p->carry)
		p->pc = get_address(p, arg.index);
	put_zjmp(vm, p, arg);
}
