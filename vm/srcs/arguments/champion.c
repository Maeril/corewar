/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   champion.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hben-yah <hben-yah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/05 18:02:59 by hben-yah          #+#    #+#             */
/*   Updated: 2019/12/14 07:13:35 by hben-yah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

int		check_champion_number(t_vm *vm, int number)
{
	t_champ	*champ;

	champ = vm->champ;
	while (champ)
	{
		if (champ->number >= 0 && champ->number == number)
			return (1);
		champ = champ->next;
	}
	return (0);
}

int		parse_champion(t_vm *vm, int number, char *file)
{
	t_champ	*champ;

	if (check_champion_number(vm, number))
		return (already_attributed_number_error());
	if (!(champ = (t_champ *)ft_memalloc(sizeof(t_champ))))
		exit_vm(vm, "malloc error : parse champion", 1);
	if (!(champ->file = ft_strdup(file)))
		exit_vm(vm, "malloc error : parse champion dup file name", 1);
	champ->id = ++vm->n_champs;
	champ->number = number;
	champ->next = vm->champ;
	vm->champ = champ;
	return (0);
}
