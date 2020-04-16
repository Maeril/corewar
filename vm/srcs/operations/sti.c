/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sti.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hben-yah <hben-yah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/24 16:52:45 by hben-yah          #+#    #+#             */
/*   Updated: 2019/12/22 11:08:36 by hben-yah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

static int	check_args_types(t_arg *args)
{
	return ((args[0].type & T_REG)
		&& (args[1].type & (T_REG | T_DIR | T_IND))
		&& (args[2].type & (T_REG | T_DIR | T_IND)));
}

static void		put_sti(t_vm *vm, t_proc *p, t_arg *args)
{
	int	add;

	put_op(vm, p);
	add = args[1].val + args[2].val;
	if (vm->options & VM_OP_UP_V)
	{
		printer(vm, 0, "charge ");
		put_arg(vm, 0, args[0]);
		printer(vm, 0, " dans ");
		put_arg(vm, 0, args[1]);
		printer(vm, 0, " + ");
		put_arg(vm, 0, args[2]);
		printer(vm, 0, " = %d (pc ", add);
		printer(vm, 0, "%d ou ", get_address(p, add));
		print_coords(vm, 0, get_address(p, add));
		printer(vm, 0, ")\n");
	}
	else
	{
		printer(vm, 0, "r%d %d %d\n",
			args[0].reg, args[1].val, args[2].val);
		printer(vm, 0, "       | -> store to %d + %d = %d ",
		args[1].val, args[2].val, add);	
		printer(vm, 0,  "(with pc and mod %d)\n",
			p->prev_pc + (add % IDX_MOD));
	}
}

void		operate_sti(t_vm *vm, t_proc *p)
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
	read_val(vm, p, &args[2]);
	if (args[1].type != T_REG)
		args[1].val = args[1].index;
	if (args[2].type != T_REG)
		args[2].val = args[2].index;
	put_sti(vm, p, args);
	args[1].type = T_IND;
	args[1].index = args[1].val + args[2].val;
	args[1].val = args[0].val;
	write_val(vm, p, args[1]);
}
