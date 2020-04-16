/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hben-yah <hben-yah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/11 11:16:33 by hben-yah          #+#    #+#             */
/*   Updated: 2019/12/18 08:42:17 by hben-yah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	put_op(t_vm *vm, t_proc *p)
{
	if (vm->options & VM_OP_UP_V)
		printer(vm, 0, "  Processus %d du Joueur %d exécute '%s' : ",
			p->id, p->number, p->op->name);
	else
		printer(vm, 0, "P %4d | %s ",
			p->id, p->op->name);
}



// void	put_args_move(t_vm *vm, int prev_pc, t_arg_type *arg, t_op *op)
// {
// 	int		len;
// 	int		i;

// 	if (vm->options & VM_OP_V)
// 	{
// 		len = op->has_ocp ? 2 : 1;
// 		i = 0;
// 		while (i < 3)
// 		{
// 			if (arg[i] == T_REG)
// 				++len;
// 			else if (arg[i] == T_DIR)
// 				len += (op->d2 ? 2 : 4);
// 			else if (arg[i] == T_IND)
// 				len += 2;
// 			++i;
// 		}
// 		put_move(vm, prev_pc, len);
// 	}
// }