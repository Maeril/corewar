/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   info.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hben-yah <hben-yah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/07 16:15:08 by hben-yah          #+#    #+#             */
/*   Updated: 2019/12/22 16:37:40 by hben-yah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void		dislay_player_name(t_vm *vm, int *y, int x, t_champ *c)
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

void		display_player_id(t_vm *vm, int *y, int x, unsigned int hex)
{
	mvwprintw(vm->display.winfo, (*y)++, x + 5,
		"Numéro                    %02x %02x %02x %02x (%d)",
		(hex >> 24) & 0xff ,
		(hex >> 16) & 0xff,
		(hex >> 8) & 0xff,
		hex & 0xff,
		hex);
}

void		display_player_infos(t_vm *vm, int *y, int x)
{
	t_champ	*c;
	int			z;

	c = vm->champ;
	*y += 2;
	while (vm && c)
	{
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
			"Lives période actuelle       %8d",	c->cur_lives);
		if (vm->options & VM_OP_A)
			mvwprintw(vm->display.winfo, *y, x + 5,
				"Aff -> %s", c->aff.str ? c->aff.str : "");
		if (!c->n_procs)
			wattroff(vm->display.winfo, COLOR_PAIR(20));
		(*y) += 2;
		c = c->next;
	}
}

static void	display_status(t_vm *vm, WINDOW *winfo, int *y, int x)
{
	if (vm->display.run == RUN)
		mvwprintw(winfo, (*y)++, x, " %C   EN MARCHE", 9654);
	else if (vm->display.run == FW)
		mvwprintw(winfo, (*y)++, x, " %C %C AVANCE", 9654, 9654);
	else if (vm->display.run == PAUSE)
		mvwprintw(vm->display.winfo, (*y)++, x, " %C%C  PAUSE ", 9612, 9612);
	else if (vm->display.run == STOP)
		mvwprintw(vm->display.winfo, (*y)++, x, " %C   TERMINE", 127937);
}

void	display_info(t_vm *vm)
{
	int x;
	int	y;

	x = 2;
	y = 2;
	werase(vm->display.winfo);
	box(vm->display.winfo, ACS_VLINE, ACS_HLINE);
	mvwprintw(vm->display.winfo, 0, 2, " Infos ");
	wattron(vm->display.winfo, A_BOLD);
	display_status(vm, vm->display.winfo, &y, x);
	mvwprintw(vm->display.winfo, y += 2, x, "Limite Cycles/seconde   %5d", vm->display.speed);
	mvwprintw(vm->display.winfo, y += 2, x, "Cycle                   %5d", vm->cycle);
	mvwprintw(vm->display.winfo, y += 2, x, "Nb processus            %5d", vm->n_procs);
	display_player_infos(vm, &y, x);
	display_current_live_breakdown(vm, &y, x);
	display_last_live_breakdown(vm, &y, x);
	mvwprintw(vm->display.winfo, y += 2, x, "CYCLE TO DIE      %5d", vm->cycle_to_die);
	mvwprintw(vm->display.winfo, y += 2, x, "CYCLE DELTA       %5d", CYCLE_DELTA);
	mvwprintw(vm->display.winfo, y += 2, x, "LIVES (max %d)    %5d", NBR_LIVE,
		vm->nbr_live);
	mvwprintw(vm->display.winfo, y += 2, x, "CHECKS (max %d)   %5d", MAX_CHECKS,
		vm->max_checks);
	wattroff(vm->display.winfo, A_BOLD);
	display_winner(vm);
}
