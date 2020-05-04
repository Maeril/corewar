/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hben-yah <hben-yah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/10 08:02:53 by hben-yah          #+#    #+#             */
/*   Updated: 2019/12/10 08:49:16 by hben-yah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	(*g_op_func_tab[18])(t_vm *, t_proc *) =
{
	0, &operate_live, &operate_ld, &operate_st, &operate_add, &operate_sub,
	&operate_and, &operate_or, &operate_xor, &operate_zjmp, &operate_ldi,
	&operate_sti, &operate_fork, &operate_lld, &operate_lldi, &operate_lfork,
	&operate_aff, 0 
};
