/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lldi.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hben-yah <hben-yah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/24 16:52:45 by hben-yah          #+#    #+#             */
/*   Updated: 2020/08/02 15:01:52 by hben-yah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

static void	put_lldi(t_vm *vm, t_proc *p, t_arg *args)
{
	int add;

	put_op(vm, p);
	add = args[0].val + args[1].val;
	if (vm->options & VM_OP_UP_V)
	{
		printer(vm, 0, "charge ");
		put_arg(vm, 0, args[0]);
		printer(vm, 0, " + ");
		put_arg(vm, 0, args[1]);
		printer(vm, 0, " = ");
		print_coords(vm, 0, add);
		printer(vm, 0, " dans ");
		put_arg(vm, 0, args[2]);
		printer(vm, 0, "\n");
	}
	else
	{
		printer(vm, 0, "%d %d r%d\n", args[0].val, args[1].val, args[2].reg);
		printer(vm, 0, "       | -> load from %d + %d = %d ",
			args[0].val, args[1].val, add);
		printer(vm, 0, "(with pc and mod %d)\n", p->prev_pc + (add % IDX_MOD));
	}
}

void		operate_lldi(t_vm *vm, t_proc *p)
{
	t_arg		args[4];

	ft_bzero(&args, sizeof(args));
	set_args_types(args, vm->field[move_pc(p, 1)]);
	if (!check_args_types(p->op, args))
		return (move_pc_through_args(p, args, p->op));
	read_arg(vm, p, &args[0]);
	read_arg(vm, p, &args[1]);
	read_arg(vm, p, &args[2]);
	if (!check_regs(args))
		return ;
	read_val(vm, p, &args[0]);
	read_val(vm, p, &args[1]);
	args[0].type = T_IND;
	args[0].index = args[0].val + args[1].val;
	read_val(vm, p, &args[0]);
	args[2].val = args[0].val;
	write_val(vm, p, args[2]);
	set_carry(p, args[2].val);
	put_lldi(vm, p, args);
}
