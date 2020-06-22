/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_tab_sizes.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myener <myener@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/23 01:09:22 by myener            #+#    #+#             */
/*   Updated: 2020/06/23 01:43:02 by myener           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/asm.h"

static int		get_param_sz(char *param, int label_size)
{
	if (param[0] == 'r')
		return (1);
	else if (param[0] == '%')
	{
		return (label_size == 1 ? 2 : 4);
	}
	else if (param[0] == ':' || (ft_atoi(param) >= INT_MIN && ft_atoi(param) <= INT_MAX))
		return (2);
	return (0);
}

static char		*get_called_label(t_line *tab, int i, int len)
{
	int		j;
	int		start;
	char	*label;
	char	*param;

	param = NULL;
	if (tab[i].param1 && tab[i].param1_sz > 1)
		param = ft_strdup(tab[i].param1);
	else if (tab[i].param2 && tab[i].param2_sz > 1)
		param = ft_strdup(tab[i].param2);
	else if (tab[i].param3 && tab[i].param3_sz > 1)
		param = ft_strdup(tab[i].param3);
	else
		return (NULL);
	j = 0;
	start = 0;
	label = NULL;
	while (param[j])
	{
		if (ft_isalphalow(param[j]) || ft_isdigit(param[j]) || param[j] == '_')
		{
			start = j;
			while (param[j] && (ft_isalphalow(param[j]) || ft_isdigit(param[j]) || param[j] == '_'))
				j++;
			label = ft_strsub(param, start, j - start);
			free(param);
			return (is_legit_label(label, tab, len) ? label : NULL);
		}
		j++;
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

int				fill_tab_sizes(t_line *tab, int len, t_tools *tools)
{
	int	i;
	int nb;
	int	l;

	i = 0;
	nb = 0;
	l = 0;
	while (i < len)
	{
		if (tab[i].instruc)
		{
			l = has_label_size(tab[i].instruc);
			nb = tab[i].nb_param;
			tools->cor_line_counter += get_correct_cor_ln(tab, i);
			tab[i].param1_sz = get_param_sz(tab[i].param1, l);
			tab[i].param2_sz = nb == 1 ? 0 : get_param_sz(tab[i].param2, l);
			tab[i].param3_sz = nb == 3 ? get_param_sz(tab[i].param3, l) : 0;
			tab[i].line_cor_ln = tab[i].param1_sz + tab[i].param2_sz + tab[i].param3_sz + 1;
			tab[i].line_cor_ln += has_cb(tab[i].instruc) ? 1 : 0;
			tab[i].relative_cor_addr = tools->cor_line_counter;
			tab[i].called_label = get_called_label(tab, i, len);
			tools->prog_size += 1;
			tools->prog_size += has_cb(tab[i].instruc) ? 1 : 0;
			tools->prog_size += tab[i].param1_sz + tab[i].param2_sz + tab[i].param3_sz;
		}
		i++;
	}
	return (1);
}
