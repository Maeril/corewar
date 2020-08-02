/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_champ.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hben-yah <hben-yah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/10 07:36:39 by hben-yah          #+#    #+#             */
/*   Updated: 2020/08/02 14:57:22 by hben-yah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

t_champ		*get_champ(t_vm *vm, int number)
{
	t_champ	*c;

	c = vm->champ;
	while (c)
	{
		if (c->number == number)
			return (c);
		c = c->next;
	}
	return (NULL);
}

t_champ		*get_champ_max_lives(t_vm *vm)
{
	t_champ	*c;
	t_champ	*max;

	max = vm->champ;
	c = max ? max->next : NULL;
	while (c)
	{
		if (c->last_live == max->last_live)
			return (NULL);
		else if (c->last_live > max->last_live)
			max = c;
		c = c->next;
	}
	return (max);
}

int			count_champs_alive(t_vm *vm)
{
	t_champ		*c;
	int			i;

	c = vm->champ;
	i = 0;
	while (c)
	{
		if (c->alive)
			++i;
		c = c->next;
	}
	return (i);
}
