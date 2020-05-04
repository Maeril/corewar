/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hben-yah <hben-yah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/08 20:26:44 by hben-yah          #+#    #+#             */
/*   Updated: 2019/12/21 19:36:49 by hben-yah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"


static void		check_options(t_vm *vm)
{
	if (vm->options)
	{
		if (vm->options & (VM_OP_D | VM_OP_S)
			&& vm->option_nb)
			dump_memory(vm);
		if (vm->options & VM_OP_C)
		{
			if (vm->display.wfield)
			{
				visualizer_handle_events(vm);
				visualizer_refresh_events(vm);
			}
			else if (vm->cycle + 1 >= vm->goto_cycle)
			{
				init_visualizer(vm);
				visualizer_handle_events(vm);
				visualizer_refresh_events(vm);
			}
		}
	}
}

static void		reset_to_next_period(t_vm *vm)
{
	t_champ *c;

	c = vm->champ;
	while (c)
	{
		c->last_lives = c->cur_lives;
		c->cur_lives = 0;
		c->alive = 0;
		c = c->next;
	}
}

void			run_vm(t_vm *vm)
{
	while (vm->cycle_to_die > 0)
	{
		check_options(vm);
		++vm->cycle;
		put_cycle(vm);
		exec_procs(vm);
		if (++vm->cycle_ctd == vm->cycle_to_die)
		{
			check_procs(vm);		
			if (++vm->max_checks == MAX_CHECKS || vm->nbr_live >= NBR_LIVE)
			{
				vm->max_checks = 0;
				vm->cycle_to_die -= CYCLE_DELTA;
				put_ctd_change(vm);
				reset_to_next_period(vm);
			}
			if (((vm->survivor = get_champ_survivor(vm))
				&& vm->cycle_to_die < 0) || !vm->n_procs)
				vm->cycle_to_die = 0;
			vm->nbr_live = 0;
			vm->cycle_ctd = 0;
		}
	}
	declare_winner(vm);
}
