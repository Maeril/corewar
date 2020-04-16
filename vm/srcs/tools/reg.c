/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reg.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hben-yah <hben-yah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/25 14:54:19 by hben-yah          #+#    #+#             */
/*   Updated: 2019/12/15 11:39:47 by hben-yah         ###   ########.fr       */
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

int		check_regs(t_arg *args)
{
	if (args[0].type == T_REG && (args[0].reg < 1 || args[0].reg > REG_NUMBER))
		return (0);
	if (args[1].type == T_REG && (args[1].reg < 1 || args[1].reg > REG_NUMBER))
		return (0);
	if (args[2].type == T_REG && (args[2].reg < 1 || args[2].reg > REG_NUMBER))
		return (0);
	return (1);
}
