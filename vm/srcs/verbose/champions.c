/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   champions.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hben-yah <hben-yah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/18 06:55:35 by hben-yah          #+#    #+#             */
/*   Updated: 2019/12/18 07:12:45 by hben-yah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	put_contestants(t_vm *vm)
{
	if (vm->options & VM_OP_UP_V)
		printer(vm, 0, "Entrée des champions...\n");
	else
		printer(vm, 0, "Introducing contestants...\n");
}


void	put_champion(t_vm *vm, t_champ *c)
{
	if (vm->options & VM_OP_UP_V)
		printer(vm, 0, "* Champion %d, pesant %d octets, \"%s\" (\"%s\") !\n",
			c->id, c->header.prog_size, c->header.prog_name,
			c->header.comment);
	else
		printer(vm, 0, "* Player %d, weighing %d bytes, \"%s\" (\"%s\") !\n",
			c->id, c->header.prog_size, c->header.prog_name,
			c->header.comment);
}
