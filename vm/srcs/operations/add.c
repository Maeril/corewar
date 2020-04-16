/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hben-yah <hben-yah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/24 16:52:45 by hben-yah          #+#    #+#             */
/*   Updated: 2019/12/18 08:10:08 by hben-yah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

static int		check_args_types(t_arg *args)
{
	return (args[0].type == T_REG
		&& args[1].type == T_REG
		&& args[2].type == T_REG);
}

static void		put_add(t_vm *vm, t_proc *p, t_arg *args)
{
	put_op(vm, p);
	if (vm->options & VM_OP_UP_V)
	{
		put_arg(vm, 0, args[0]);
		printer(vm, 0, " + ");
		put_arg(vm, 0, args[1]);
		printer(vm, 0, " = ");
		put_arg(vm, 0, args[2]);
		printer(vm, 0, "\n");
	}
	else
		printer(vm, 0, "r%d r%d r%d\n", args[0].reg, args[1].reg, args[2].reg);
}

void			operate_add(t_vm *vm, t_proc *p)
{
	t_arg		args[4];

	ft_bzero(&args, sizeof(args));
	set_args_types(args, vm->field[move_pc(p, 1)]);
	if (!check_args_types(args))
		return (move_pc_through_args(p, args, p->op));
	read_arg(vm, p, &args[0]);
	read_arg(vm, p, &args[1]);
	read_arg(vm, p, &args[2]);
	if (!check_regs(args))
		return ;
	read_val(vm, p, &args[0]);
	read_val(vm, p, &args[1]);
	args[2].val = args[0].val + args[1].val;
	write_val(vm, p, args[2]);
	set_carry(p, args[2].val);
	put_add(vm, p, args);
}
