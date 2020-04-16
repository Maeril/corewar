/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hben-yah <hben-yah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/07 16:17:47 by hben-yah          #+#    #+#             */
/*   Updated: 2019/12/22 15:58:24 by hben-yah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	init_colors(void)
{
	start_color();

	init_pair(20, 8, COLOR_BLACK);
	init_pair(RCOLOR - 1, 8, 8);
	
	init_pair(1, P1_COLOR, COLOR_BLACK);
	init_pair(WCOLOR - 2, COLOR_WHITE, P1_COLOR);
	init_pair(RCOLOR - 2, COLOR_BLACK, P1_COLOR);
	
	init_pair(2, P2_COLOR, COLOR_BLACK);
	init_pair(WCOLOR - 3, COLOR_WHITE, P2_COLOR);
	init_pair(RCOLOR - 3, COLOR_BLACK, P2_COLOR);
	
	init_pair(3, P3_COLOR, COLOR_BLACK);
	init_pair(WCOLOR - 4, COLOR_WHITE, P3_COLOR);
	init_pair(RCOLOR - 4, COLOR_BLACK, P3_COLOR);
	
	init_pair(4, P4_COLOR, COLOR_BLACK);
	init_pair(WCOLOR - 5, COLOR_WHITE, P4_COLOR);
	init_pair(RCOLOR - 5, COLOR_BLACK, P4_COLOR);
	
	init_pair(NORMAL_COLOR, COLOR_WHITE, COLOR_BLACK);
	
	init_pair(RCOLOR - NORMAL_COLOR - 1, COLOR_BLACK, COLOR_WHITE);
	
	init_pair(ERR_COLOR, COLOR_RED, COLOR_BLACK);
	init_pair(RCOLOR - ERR_COLOR - 1, COLOR_WHITE, COLOR_RED);
}

int		get_champion_color(t_vm *vm, int reg)
{
	t_champ	*c;

	c = vm->champ;
	while (c)
	{
		if (c->number == reg)
			return (ft_abs(c->id));
		c = c->next;
	}
	return (NORMAL_COLOR);
}

void	display_color(t_vm *vm, t_proc *p, int index, int size)
{
	int		color;
	int		address;

	if (vm->options & (VM_OP_C | VM_OP_S))
	{
		color = get_champion_color(vm, p->number);
		while (size--)
		{
			address = (index + size) % MEM_SIZE;
			if (vm->cycle > 0)
				vm->cells[address].modified = 1;
			vm->cells[address].live = 0;
			vm->cells[address].cycle = vm->cycle;
			vm->cells[address].color = color;
		}
	}
}

// void	visu_killpc(t_vm *vm, t_proc *p)
// {
// 	if (!(vm->flags & (FLAG_NCURSES | FLAG_DUMPC | FLAG_SLEEP)))
// 		return ;
// 	if (vm->colors[p->pc] >= RCOLOR - MAX_PLAYERS)
// 		vm->colors[p->pc] = ft_abs(vm->colors[p->pc] - RCOLOR);
// }

// void	visu_movepc(t_vm *vm, t_proc *p)
// {
// 	unsigned int	oldpc;
// 	unsigned int	newpc;

// 	if (!(vm->flags & (FLAG_NCURSES | FLAG_DUMPC | FLAG_SLEEP)))
// 		return ;
// 	oldpc = p->prev_pc % MEM_SIZE;
// 	newpc = p->pc % MEM_SIZE;
// 	if (vm->colors[oldpc] >= RCOLOR - MAX_PLAYERS)
// 		vm->colors[oldpc] = ft_abs(vm->colors[oldpc] - RCOLOR);
// 	if (vm->arena[newpc])
// 		vm->colors[newpc] = RCOLOR - vm->colors[newpc];
// }