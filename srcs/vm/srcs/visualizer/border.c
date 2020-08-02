/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   border.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hben-yah <hben-yah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/08 11:29:20 by hben-yah          #+#    #+#             */
/*   Updated: 2019/12/14 07:20:13 by hben-yah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	display_borders(t_display *d)
{
	box(d->wfield, ACS_VLINE, ACS_HLINE);
	mvwprintw(d->wfield, 0, 2, " Champs de bataille ");
	box(d->winfo, ACS_VLINE, ACS_HLINE);
	mvwprintw(d->winfo, 0, 2, " Infos ");
	box(d->wleg, ACS_VLINE, ACS_HLINE);
	mvwprintw(d->wleg, 0, 2, " Légende ");
}
