/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hben-yah <hben-yah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/11 11:16:33 by hben-yah          #+#    #+#             */
/*   Updated: 2020/08/01 12:20:28 by hben-yah         ###   ########.fr       */
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
