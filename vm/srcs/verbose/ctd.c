/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ctd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hben-yah <hben-yah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/18 08:22:40 by hben-yah          #+#    #+#             */
/*   Updated: 2019/12/18 08:28:03 by hben-yah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void		put_ctd_change(t_vm *vm)
{
	if (vm->options & VM_OP_UP_V)
		printer(vm, 0, "Le Cycle To Die descend à %d\n", vm->cycle_to_die);
	else
		printer(vm, 0, "Cycle to die is now %d\n", vm->cycle_to_die);
}