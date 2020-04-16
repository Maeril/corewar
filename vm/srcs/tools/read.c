/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hben-yah <hben-yah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/11 10:46:46 by hben-yah          #+#    #+#             */
/*   Updated: 2019/12/22 10:54:56 by hben-yah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

uintmax_t	read_field(t_vm *vm, t_proc *p, size_t size)
{
	uintmax_t	val;

	val = 0;
	while (size--)
		val = (val << 8) | vm->field[move_pc(p, 1)];
	return (val);
}

uintmax_t	read_field_at(t_vm *vm, int i, size_t size)
{
	uintmax_t	val;

	val = 0;
	while (size--)
		val = (val << 8) | vm->field[i++];
	return (val);
}

// int			read_arg(t_vm *vm, t_proc *p, t_arg_type arg, int idx)
// {
// 	int		ret;

// 	ret = 0;
// 	if (arg == T_REG)
// 	{
// 		ret = read_field(vm, p, 1);
// 		printer(vm, 0, "r%d ", ret);
// 		ret = get_reg_val(p, ret);
// 	}
// 	else if (arg == T_DIR)
// 		ret = read_field(vm, p, p->op->d2 ? 2 : 4);
// 	else if (arg == T_IND)
// 	{
// 		ret = read_field(vm, p, 2);
// 		if (ret & 0x8000)
// 			ret = ret - 0xFFFF - 1;
// 		ret = p->prev_pc + (idx ? ret % IDX_MOD : ret);
// 		print_coords(vm, 0, ret);
// 		printer(vm, 0, " ");
// 		ret = read_field_at(vm, ret, 4);
// 	}
// 	if (ret & 0x80000000)
// 		ret = ret - 0xFFFFFFFF - 1;
// 	return (ret);
// }

void		read_arg(t_vm *vm, t_proc *p, t_arg *arg)
{
	if (arg->type == T_REG)
		arg->reg = (unsigned char)read_field(vm, p, 1);
	else if (arg->type == T_DIR)
	{
		if (p->op->d2)
		{
			arg->index = read_field(vm, p, 2);
			if (arg->index & 0x8000)
				arg->index = arg->index - 0xFFFF - 1;
		}
		else
			arg->val = read_field(vm, p, 4);
	}	
	else if (arg->type == T_IND)
	{
		arg->index = read_field(vm, p, 2);
		if (arg->index & 0x8000)
			arg->index = arg->index - 0xFFFF - 1;
	}
}

void		read_val(t_vm *vm, t_proc *p, t_arg *arg)
{
	if (arg->type == T_REG)
		arg->val = get_reg_val(p, arg->reg);
	else if (arg->type == T_IND || (arg->type == T_DIR && p->op->d2))
		arg->val = read_field_at(vm, get_address(p, arg->index), DIR_SIZE);
}
