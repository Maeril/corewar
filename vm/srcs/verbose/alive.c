/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alive.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hben-yah <hben-yah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/18 07:12:56 by hben-yah          #+#    #+#             */
/*   Updated: 2019/12/18 07:24:15 by hben-yah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	put_alive(t_vm *vm, t_champ *c)
{
	if (vm->options & VM_OP_UP_V)
		printer(vm, 0, "Le champion %d (%s) a été rapporté comme vivant !\n",
			c->id, c->header.prog_name);
	else
		printer(vm, 0, "Player %d (%s) is said to be alive\n",
			c->id, c->header.prog_name);
}
