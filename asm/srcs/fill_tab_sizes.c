/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_tab_sizes.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myener <myener@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/23 01:09:22 by myener            #+#    #+#             */
/*   Updated: 2020/07/01 06:04:41 by myener           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/asm.h"

static char		*get_called_label_helper(char *label, t_line *tab, int len)
{
	if (is_legit_label(label, tab, len))
		return (label);
	else
		label ? free(label) : 0;
	return (NULL);
}

static char		*get_called_label(t_line *tab, int i, int len)
{
	int		j;
	int		start;
	char	*label;
	char	*param;

	param = NULL;
	if (!(param = get_param(tab, i, param)))
		return (NULL);
	j = -1;
	start = 0;
	label = NULL;
	while (param[++j])
		if (ft_isalphalow(param[j]) || ft_isdigit(param[j]) || param[j] == '_')
		{
			start = j;
			while (param[j] && (ft_isalphalow(param[j])
				|| ft_isdigit(param[j]) || param[j] == '_'))
				j++;
			label = ft_strsub(param, start, j - start);
			param ? free(param) : 0;
			return (get_called_label_helper(label, tab, len));
		}
	param ? free(param) : 0;
	return (NULL);
}

static int		get_correct_cor_ln(t_line *tab, int i)
{
	int j;

	j = i;
	if (i > 0)
	{
		while (j > 0 && tab[j].line_cor_ln == 0)
			j--;
		return (tab[j].line_cor_ln);
	}
	return (0);
}

static int		fill_tab_sizes_helper(int i, t_line *tab, t_tools *tools)
{
	int j;

	i--;
	j = i;
	while (j > 0 && !tab[j].p1_sz)
		j--;
	if (!tab[i].relative_cor_addr)
	{
		tab[i].relative_cor_addr = tools->cor_line_counter;
		tab[i].relative_cor_addr += tab[j].p1_sz + tab[j].p2_sz + tab[j].p3_sz;
		tab[i].relative_cor_addr += 1 + has_cb(tab[j].instruc) ? 1 : 0;
	}
	return (1);
}

int				fill_tab_sizes(t_line *tab, t_tools *tools)
{
	int	i;
	int nb;
	int	l;

	i = -1;
	nb = 0;
	l = 0;
	while (++i < tools->tablen)
		if (tab[i].instruc)
		{
			l = has_label_size(tab[i].instruc);
			nb = tab[i].nb_param;
			tools->cor_line_counter += get_correct_cor_ln(tab, i);
			tab[i].p1_sz = get_param_sz(tab[i].p1, l);
			tab[i].p2_sz = nb == 1 ? 0 : get_param_sz(tab[i].p2, l);
			tab[i].p3_sz = nb == 3 ? get_param_sz(tab[i].p3, l) : 0;
			tab[i].line_cor_ln = tab[i].p1_sz + tab[i].p2_sz + tab[i].p3_sz + 1;
			tab[i].line_cor_ln += has_cb(tab[i].instruc) ? 1 : 0;
			tab[i].relative_cor_addr = tools->cor_line_counter;
			tab[i].called_label = get_called_label(tab, i, tools->tablen);
			tools->prog_size += 1;
			tools->prog_size += has_cb(tab[i].instruc) ? 1 : 0;
			tools->prog_size += tab[i].p1_sz + tab[i].p2_sz + tab[i].p3_sz;
		}
	return (fill_tab_sizes_helper(i, tab, tools));
}
