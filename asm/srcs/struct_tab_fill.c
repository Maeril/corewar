/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_tab_fill.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myener <myener@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/08 16:35:00 by myener            #+#    #+#             */
/*   Updated: 2020/06/23 20:36:23 by myener           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/asm.h"

static int	fill_lonely_labels(t_line *tab, int len)
{
	int i;
	int	j;

	i = 0;
	j = 0;
	while (++i < len)
		if (tab[i].label && !tab[i].relative_cor_addr)
		{
			j = i;
			while (j < len && !tab[j].relative_cor_addr)
				j++;
			tab[i].relative_cor_addr = tab[j].relative_cor_addr;
		}
	while (i > 0 && !tab[i].label && !tab[i].instruc)
		i--;
	if (tab[i].label && !tab[i].instruc)
	{
		j = i;
		while (j > 0 && !tab[j].instruc)
			j--;
		tab[i].relative_cor_addr = tab[j].relative_cor_addr + tab[j].p1_sz
			+ tab[j].p2_sz + tab[j].p3_sz + has_cb(tab[j].instruc) + 1;
	}
	return (1);
}

int			struct_tab_fill(char **input, t_line *struct_tab, t_tools *tools)
{
	if (!fill_tab_input(input, struct_tab, tools))
		return (0);
	if (!fill_tab_sizes(struct_tab, ft_tablen(input), tools))
		return (0);
	if (!fill_lonely_labels(struct_tab, ft_tablen(input)))
		return (0);
	return (1);
}
