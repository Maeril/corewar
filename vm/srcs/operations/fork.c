/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hben-yah <hben-yah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/24 16:52:45 by hben-yah          #+#    #+#             */
/*   Updated: 2019/12/21 10:08:56 by hben-yah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

static void		put_fork(t_vm *vm, t_proc *p, t_proc *new, t_arg arg)
{
	put_op(vm, p);
	if (vm->options & VM_OP_UP_V)
	{
		printer(vm, 0, "fork dans ");
		printer(vm, 0, " %d ", arg.index);
		print_coords(vm, 0, new->pc);
		printer(vm, 0, "\n");
	}
	else
		printer(vm, 0, "%d (%d)\n", arg.index, new->pc);
}

void		operate_fork(t_vm *vm, t_proc *p)
{
	t_arg	arg;
	t_proc	*new;

	ft_bzero(&arg, sizeof(arg));
	arg.type = T_DIR;
	read_arg(vm, p, &arg);
	new = fork_proc(vm, p);
	new->pc = get_address(new, arg.index);
	put_fork(vm, p, new, arg);
	new->op = NULL;
}
