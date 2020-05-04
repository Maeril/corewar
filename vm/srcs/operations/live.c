/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   live.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hben-yah <hben-yah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/24 16:52:45 by hben-yah          #+#    #+#             */
/*   Updated: 2019/12/22 13:58:02 by hben-yah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

static void		display_live(t_vm *vm, t_proc *p)
{
	if (vm->options & VM_OP_C)
	{
		vm->cells[p->prev_pc].live = 1;
		vm->cells[p->prev_pc].cycle = vm->cycle;
	}
}

static void		set_alive(t_vm *vm, int number)
{
	t_champ *c;

	c = vm->champ;
	while (c)
	{
		if (number == c->number)
		{
			c->alive = 1;
			c->last_live = vm->cycle;
			vm->last_live_champ = c;
			++c->cur_lives;
			put_alive(vm, c);
			break ;
		}
		c = c->next;
	}
}

void			operate_live(t_vm *vm, t_proc *p)
{
	t_arg	arg;
	
	ft_bzero(&arg, sizeof(arg));
	arg.type = T_DIR;
	read_arg(vm, p, &arg);
	put_op(vm, p);
	printer(vm, 0, "%d\n", arg.val);
	set_alive(vm, arg.val);
	++p->lives;
	p->last_live = vm->cycle;
	++vm->nbr_live;
	display_live(vm, p);
}
