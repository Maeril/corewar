/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hben-yah <hben-yah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/15 08:19:34 by hben-yah          #+#    #+#             */
/*   Updated: 2019/12/15 11:22:45 by hben-yah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void			put_arg(t_vm *vm, int force, t_arg arg)
{
	if (arg.type == T_REG)
		printer(vm, force, "r%d (%d)", arg.reg, arg.val);
	else if (arg.type == T_IND)
	{
		print_coords(vm, force, arg.index);
		printer(vm, force, " (%d)", arg.val);
	}
	else
		printer(vm, force, "%d", arg.reg, arg.val);
}

void			put_cycle(t_vm *vm)
{
	if (vm->options & VM_OP_UP_V)
		printer(vm, 0, "Cycle %d\n", vm->cycle);
	else
		printer(vm, 0, "It is now cycle %d\n", vm->cycle);
}