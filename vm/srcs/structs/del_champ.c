/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   del_champ.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hben-yah <hben-yah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/24 09:05:49 by hben-yah          #+#    #+#             */
/*   Updated: 2019/12/10 07:49:10 by hben-yah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	del_champ(t_champ **champ)
{
	t_champ *todel;

	if (champ && *champ)
	{
		todel = *champ;
		*champ = (*champ)->next;
		free(todel->file);
		free(todel);
	}
}

void	del_champ_lst(t_champ **lst)
{
	if (lst)
		while (*lst)
			del_champ(lst);
}
