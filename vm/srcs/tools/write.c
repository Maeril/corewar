/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hben-yah <hben-yah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/12 08:53:22 by hben-yah          #+#    #+#             */
/*   Updated: 2019/12/22 10:54:44 by hben-yah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	write_field_at(t_vm *vm, int i, intmax_t val, size_t size)
{
	while (size--)
		vm->field[i++ % MEM_SIZE] = (val >> (size * 8)) & 0xFF;
}

void		write_val(t_vm *vm, t_proc *p, t_arg arg)
{
	if (arg.type == T_REG)
		set_reg_val(p, arg.reg, arg.val);
	else if (arg.type == T_IND || (arg.type == T_DIR && p->op->d2))
	{
		write_field_at(vm, get_address(p, arg.index), arg.val, DIR_SIZE);
		display_color(vm, p, get_address(p, arg.index), DIR_SIZE);
	}
}
