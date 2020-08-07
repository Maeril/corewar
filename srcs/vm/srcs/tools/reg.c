/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reg.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hben-yah <hben-yah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/25 14:54:19 by hben-yah          #+#    #+#             */
/*   Updated: 2020/08/07 10:31:53 by hben-yah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void		set_reg_val(t_proc *p, int reg, uintmax_t val)
{
	p->regs[reg - 1] = val;
}

uintmax_t	get_reg_val(t_proc *p, int reg)
{
	return (p->regs[reg - 1]);
}

int			check_regs(t_op *op, t_arg *args)
{
	int i;

	i = 0;
	while (i < 3)
	{
		if (op->args_types[i] && args[i].type == T_REG
			&& (args[i].reg < 1 || args[i].reg > REG_NUMBER))
			return (0);
		++i;
	}
	return (1);
}
