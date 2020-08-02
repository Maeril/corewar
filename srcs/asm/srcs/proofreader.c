/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   proofreader.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tferrieu <tferrieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/22 00:54:28 by myener            #+#    #+#             */
/*   Updated: 2020/08/02 18:46:08 by tferrieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/asm.h"

static int	is_reg(char *param)
{
	return (param[0] == 'r' ? 1 : 0);
}

static int	is_dir(char *param)
{
	return (param[0] == DIRECT_CHAR ? 1 : 0);
}

static int	is_ind(char *param)
{
	return (!is_dir(param) && !is_reg(param) ? 1 : 0);
}

static int	proofreader_helper(t_line *tab, int i)
{
	if ((!ft_strcmp(tab[i].instruc, "and") && !is_reg(tab[i].p3))
		|| (!ft_strcmp(tab[i].instruc, "or") && !is_reg(tab[i].p3))
		|| (!ft_strcmp(tab[i].instruc, "xor") && !is_reg(tab[i].p3))
		|| (!ft_strcmp(tab[i].instruc, "zjmp") && !is_dir(tab[i].p1))
		|| (!ft_strcmp(tab[i].instruc, "ldi") && (is_ind(tab[i].p2)
		|| !is_reg(tab[i].p3)))
		|| (!ft_strcmp(tab[i].instruc, "sti") && (!is_reg(tab[i].p1)
		|| is_ind(tab[i].p3)))
		|| (!ft_strcmp(tab[i].instruc, "fork") && !is_dir(tab[i].p1))
		|| (!ft_strcmp(tab[i].instruc, "lld") && (is_reg(tab[i].p1)
		|| !is_reg(tab[i].p2)))
		|| (!ft_strcmp(tab[i].instruc, "lldi") && (is_ind(tab[i].p2)
		|| !is_reg(tab[i].p3)))
		|| (!ft_strcmp(tab[i].instruc, "lfork") && !is_dir(tab[i].p1))
		|| (!ft_strcmp(tab[i].instruc, "aff") && !is_reg(tab[i].p1)))
		return (0);
	return (1);
}

int			proofreader(t_line *t, int len)
{
	int i;

	i = -1;
	while (++i < len)
	{
		if (t[i].instruc)
		{
			if ((one_p(t[i].instruc) && (!t[i].p1 || t[i].p2 || t[i].p3))
			|| (two_p(t[i].instruc) && (!t[i].p1 || !t[i].p2 || t[i].p3))
			|| (three_p(t[i].instruc) && (!t[i].p1 || !t[i].p2 || !t[i].p3)))
				return (0);
			if ((!ft_strcmp(t[i].instruc, "live") && !is_dir(t[i].p1))
				|| (!ft_strcmp(t[i].instruc, "ld") && (is_reg(t[i].p1)
				|| !is_reg(t[i].p2))) || (!ft_strcmp(t[i].instruc, "st")
				&& (!is_reg(t[i].p1)))
				|| (!ft_strcmp(t[i].instruc, "add") && !(is_reg(t[i].p1)
				&& is_reg(t[i].p2) && is_reg(t[i].p3)))
				|| (!ft_strcmp(t[i].instruc, "sub") && !(is_reg(t[i].p1)
				&& is_reg(t[i].p2) && is_reg(t[i].p3))))
				return (0);
			else if (!(proofreader_helper(t, i)))
				return (0);
		}
	}
	return (1);
}
