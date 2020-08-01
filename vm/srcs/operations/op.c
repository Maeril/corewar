/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hben-yah <hben-yah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/10 08:02:53 by hben-yah          #+#    #+#             */
/*   Updated: 2020/08/01 12:00:14 by hben-yah         ###   ########.fr       */
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

int		check_args_types(t_op *op, t_arg *args)
{
	return ((op->args_types[0] & args[0].type) == args[0].type
		&& (op->args_types[1] & args[1].type) == args[1].type
		&& (op->args_types[2] & args[2].type) == args[2].type);
}
