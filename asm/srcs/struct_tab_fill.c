/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_tab_fill.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myener <myener@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/08 16:35:00 by myener            #+#    #+#             */
/*   Updated: 2020/07/01 05:57:13 by myener           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/asm.h"

int			stock_instruct_clean_free(char *n, int ret)
{
	if (n)
		free(n);
	return (ret);
}

int			get_param_sz(char *param, int label_size)
{
	if (param[0] == 'r')
		return (1);
	else if (param[0] == '%')
		return (label_size == 1 ? 2 : 4);
	else if (param[0] == ':' || (ft_atoi(param) >= INT_MIN
		&& ft_atoi(param) <= INT_MAX))
		return (2);
	return (0);
}

char		*get_param(t_line *tab, int i, char *param)
{
	if (tab[i].p1 && tab[i].p1_sz > 1)
		param = ft_strdup(tab[i].p1);
	else if (tab[i].p2 && tab[i].p2_sz > 1)
		param = ft_strdup(tab[i].p2);
	else if (tab[i].p3 && tab[i].p3_sz > 1)
		param = ft_strdup(tab[i].p3);
	else
		return (NULL);
	return (param);
}

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
			if (j < len)
				tab[i].relative_cor_addr = tab[j].relative_cor_addr;
		}
	return (1);
}

int			struct_tab_fill(char **input, t_line *struct_tab, t_tools *tools)
{
	if (!fill_tab_input(input, struct_tab, tools))
		return (0);
	if (!fill_tab_sizes(struct_tab, tools))
		return (0);
	if (!fill_lonely_labels(struct_tab, tools->tablen))
		return (0);
	return (1);
}
