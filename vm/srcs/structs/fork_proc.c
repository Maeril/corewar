/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_proc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hben-yah <hben-yah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/12 07:47:08 by hben-yah          #+#    #+#             */
/*   Updated: 2019/12/21 10:33:47 by hben-yah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

t_proc			*fork_proc(t_vm *vm, t_proc *p)
{
	t_proc	*new;
	int		i;

	new = insert_proc(vm, new_proc(vm), p->number);
	new->prev_pc = p->prev_pc;
	new->pc = p->prev_pc;
	i = -1;
	while (++i < REG_NUMBER)
		new->regs[i] = p->regs[i];
	new->carry = p->carry;
	new->lives = p->lives;
	new->last_live = p->last_live;
	new->sleep = p->sleep;
	new->op = p->op;
	new->champ = p->champ;
	return (new);
}
