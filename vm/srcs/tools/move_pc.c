/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_pc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hben-yah <hben-yah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/11 11:07:03 by hben-yah          #+#    #+#             */
/*   Updated: 2019/12/20 10:58:53 by hben-yah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void			move_pc_through_args(t_proc *p, t_arg *args, t_op *op)
{
	int		i;

	// if (op->has_ocp)
	// 	p->pc += 12;
	i = 0;
	while (i < op->n_args)
	{
		if (args[i].type == T_REG)
			++p->pc;
		else if (args[i].type == T_DIR)
			p->pc += op->d2 ? 2 : 4;
		else if (args[i].type == T_IND)
			p->pc += 2;
		++i;
	}
}

int			get_address(t_proc *p, int index)
{
	char	idx_mod;
	int	address;

	idx_mod = p->op && (p->op->op_code < 13 || p->op->op_code > 15);
	address = p->prev_pc + (idx_mod ? index % IDX_MOD : index);
	if (address & 0x8000)
		address = address - 0xFFFF - 1;
	return ((address % MEM_SIZE) + (address < 0 ? MEM_SIZE : 0));
}

int				move_pc(t_proc *p, int i)
{
	p->pc += i;
	return ((p->pc = (p->pc % MEM_SIZE) + (p->pc < 0 ? MEM_SIZE : 0)));
}
