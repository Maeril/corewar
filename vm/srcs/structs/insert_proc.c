/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   insert_proc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hben-yah <hben-yah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/12 07:56:21 by hben-yah          #+#    #+#             */
/*   Updated: 2019/12/21 11:31:58 by hben-yah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

t_proc			*insert_proc(t_vm *vm, t_proc *new, int n_champ)
{
	t_champ		*c;

	if ((c = get_champ(vm, n_champ)))
		++c->n_procs;
	new->id = ++vm->id_procs;
	new->number = n_champ;
	new->next = vm->proc;
	vm->proc = new;
	++vm->n_procs;
	return (new);
}