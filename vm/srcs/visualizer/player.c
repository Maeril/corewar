/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hben-yah <hben-yah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/02 14:20:52 by hben-yah          #+#    #+#             */
/*   Updated: 2020/08/02 15:07:59 by hben-yah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	dislay_player_name(t_vm *vm, int *y, int x, t_champ *c)
{
	int		i;
	int		max;
	char	*name;

	i = 0;
	max = 43;
	name = c->header.prog_name;
	x += 3;
	wattron(vm->display.winfo, COLOR_PAIR(ft_abs(c->id)));
	mvwprintw(vm->display.winfo, *y, x, "Champion %d : ", c->id);
	x += 13;
	while (name[i] && max--)
	{
		if (name[i] == '\n')
		{
			mvwprintw(vm->display.winfo, *y, x, "%c", '~');
			break ;
		}
		mvwprintw(vm->display.winfo, *y, x++, "%c", name[i++]);
	}
	wattroff(vm->display.winfo, COLOR_PAIR(ft_abs(c->id)));
	++(*y);
}

void	display_player_id(t_vm *vm, int *y, int x, unsigned int hex)
{
	mvwprintw(vm->display.winfo, (*y)++, x + 5,
		"Numéro                    %02x %02x %02x %02x (%d)",
		(hex >> 24) & 0xff,
		(hex >> 16) & 0xff,
		(hex >> 8) & 0xff,
		hex & 0xff,
		hex);
}

void	display_player_infos(t_vm *vm, int *y, int x, t_champ *c)
{
	int		z;

	z = *y;
	wattron(vm->display.winfo, COLOR_PAIR(RCOLOR - ft_abs(c->id) - 1));
	while (z < (*y + 6))
		mvwprintw(vm->display.winfo, z++, x, " ");
	wattroff(vm->display.winfo, COLOR_PAIR(RCOLOR - ft_abs(c->id) - 1));
	dislay_player_name(vm, y, x, c);
	if (!c->n_procs)
		wattron(vm->display.winfo, COLOR_PAIR(20));
	display_player_id(vm, y, x, c->number);
	mvwprintw(vm->display.winfo, (*y)++, x + 5,
		"Nb processus                 %8d", c->n_procs);
	mvwprintw(vm->display.winfo, (*y)++, x + 5,
		"Dernier live (cycle)         %8d", c->last_live);
	mvwprintw(vm->display.winfo, (*y)++, x + 5,
		"Lives période actuelle       %8d", c->cur_lives);
	if (vm->options & VM_OP_A)
		mvwprintw(vm->display.winfo, *y, x + 5,
			"Aff -> %s", c->aff.str ? c->aff.str : "");
	if (!c->n_procs)
		wattroff(vm->display.winfo, COLOR_PAIR(20));
}
