/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colrow.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hben-yah <hben-yah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/08 11:30:09 by hben-yah          #+#    #+#             */
/*   Updated: 2019/12/14 10:14:59 by hben-yah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	display_colrow(t_display *d)
{
	int	x;
	int y;
	int	i;
	int	max;

	max = d->el_per_line;
	x = d->field.x + 1;
	y = d->field.y - 1;
	i = 0;
	while (i < max)
	{
		mvprintw(y, x, " %02d", i++);
		x += 3;
	}
	x = d->field.x - 3;
	y = d->field.y + 1;
	i = 0;
	while (i < max)
		mvprintw(y++, x, "%02d", i++);
	refresh();
}
