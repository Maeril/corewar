/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   info.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hben-yah <hben-yah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/07 16:15:08 by hben-yah          #+#    #+#             */
/*   Updated: 2020/08/02 14:44:41 by hben-yah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void		display_players_infos(t_vm *vm, int *y, int x)
{
	t_champ	*c;

	c = vm->champ;
	*y += 2;
	while (vm && c)
	{
		display_player_infos(vm, y, x, c);
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

static void	display_info_end(t_vm *vm, int y, int x)
{
	mvwprintw(vm->display.winfo, y += 2, x, "CYCLE TO DIE      %5d",
		vm->cycle_to_die);
	mvwprintw(vm->display.winfo, y += 2, x, "CYCLE DELTA       %5d",
		CYCLE_DELTA);
	mvwprintw(vm->display.winfo, y += 2, x, "LIVES (max %d)    %5d",
		NBR_LIVE, vm->nbr_live);
	mvwprintw(vm->display.winfo, y += 2, x, "CHECKS (max %d)   %5d",
		MAX_CHECKS, vm->max_checks);
	wattroff(vm->display.winfo, A_BOLD);
	display_winner(vm);
}

void		display_info(t_vm *vm)
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
	mvwprintw(vm->display.winfo, y += 2, x, "Limite Cycles/seconde   %5d",
		vm->display.speed);
	mvwprintw(vm->display.winfo, y += 2, x, "Cycle                   %5d",
		vm->cycle);
	mvwprintw(vm->display.winfo, y += 2, x, "Nb processus            %5d",
		vm->n_procs);
	display_players_infos(vm, &y, x);
	display_current_live_breakdown(vm, &y, x);
	display_last_live_breakdown(vm, &y, x);
	display_info_end(vm, y, x);
}
