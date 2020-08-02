/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   winner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hben-yah <hben-yah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/10 09:39:34 by hben-yah          #+#    #+#             */
/*   Updated: 2020/08/02 14:15:37 by hben-yah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

static void		display_winner_border(t_vm *vm, int len, int y, int x)
{
	int		i;

	mvwprintw(vm->display.winfo, y - 2, x - 5, "%*s", len + 10, "");
	mvwprintw(vm->display.winfo, y + 2, x - 5, "%*s", len + 10, "");
	i = 0;
	while (i < 3)
	{
		mvwprintw(vm->display.winfo, (y - 1) + i, x - 5, "  ");
		mvwprintw(vm->display.winfo, (y - 1) + i, x + len + 3, "  ");
		++i;
	}
}

static void		display_winner_name(t_vm *vm, t_champ *c, int y, int x)
{
	int	len;

	wattron(vm->display.winfo, A_BOLD);
	if (c)
	{
		len = ft_min(ft_strlen(c->header.prog_name), vm->display.info.col - 10);
		mvwprintw(vm->display.winfo, y, x, "%.*s", len, c->header.prog_name);
		wattron(vm->display.winfo, COLOR_PAIR(RCOLOR - ft_abs(c->id) - 1));
		display_winner_border(vm, len, y, x);
		wattroff(vm->display.winfo, COLOR_PAIR(RCOLOR - ft_abs(c->id) - 1));
	}
	x = (vm->display.info.col / 2) - 9;
	mvwprintw(vm->display.winfo, y + 4, x - 5, "%s",
		"Appuyez sur END pour quitter");
	wattroff(vm->display.winfo, A_BOLD);
}

void			display_winner(t_vm *vm)
{
	int	x;

	if (vm->cycle_to_die <= 0)
	{
		x = (vm->display.info.col / 2)
			- (ft_strlen(vm->last_live_champ->header.prog_name) / 2);
		display_winner_name(vm, vm->last_live_champ, 50, x);
	}
}
