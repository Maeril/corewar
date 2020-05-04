/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   st.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hben-yah <hben-yah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/24 16:52:45 by hben-yah          #+#    #+#             */
/*   Updated: 2019/12/20 06:31:43 by hben-yah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

static int	check_args_types(t_arg *args)
{
	return ((args[0].type & T_REG)
		&& (args[1].type & (T_REG | T_IND)));
}

static void		put_st(t_vm *vm, t_proc *p, t_arg *args)
{
	put_op(vm, p);
	if (vm->options & VM_OP_UP_V)
	{
		printer(vm, 0, "charge ");
		put_arg(vm, 0, args[0]);
		printer(vm, 0, " dans ");
		put_arg(vm, 0, args[1]);
		printer(vm, 0, "\n");
	}
	else
	{
		if (args[1].type == T_REG)
			printer(vm, 0, "r%d %d\n", args[0].reg, args[1].reg);
		else if (args[1].type == T_IND)
			printer(vm, 0, "r%d %d\n", args[0].reg, args[1].index);
	}
}

void		operate_st(t_vm *vm, t_proc *p)
{
	t_arg		args[4];

	ft_bzero(&args, sizeof(t_arg));
	set_args_types(args, vm->field[move_pc(p, 1)]);
	if (!check_args_types(args))
		return (move_pc_through_args(p, args, p->op));
	read_arg(vm, p, &args[0]);
	read_arg(vm, p, &args[1]);
	if (!check_regs(args))
		return ;
	read_val(vm, p, &args[0]);
	args[1].val = args[0].val;
	write_val(vm, p, args[1]);
	put_st(vm, p, args);
}
