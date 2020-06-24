/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_tab_input.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myener <myener@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/23 01:06:21 by myener            #+#    #+#             */
/*   Updated: 2020/06/24 21:09:03 by myener           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/asm.h"

static int	stock_instruc_helper(t_line *struct_tab, char *line, int i, char *n)
{
	int	start;

	i++;
	while (line[i] && ft_isblank(line[i]))
		i++;
	start = i;
	while (line[i] && (has_two_params(n) ? !ft_isblank(line[i])
		&& line[i] != '\n' : line[i] != ','))
		i++;
	struct_tab->p2 = ft_strsub(line, start, i - start);
	struct_tab->nb_param = has_two_params(n) ? 2 : struct_tab->nb_param;
	n && has_two_params(n) ? free(n) : 0;
	if (has_two_params(n))
		return (1);
	i++;
	while (line[i] && ft_isblank(line[i]))
		i++;
	start = i;
	while (line[i] && !ft_isblank(line[i]))
		i++;
	struct_tab->p3 = ft_strsub(line, start, i - start);
	struct_tab->nb_param = 3;
	n ? free(n) : 0;
	return (1);
}

static int	stock_instruction(t_line *struct_tab, char *line, int i)
{
	int		start;
	char	*n;
	char	*tmp;
	int		one;

	while (line[i] && ft_isblank(line[i]))
		i++;
	if (line[i] == '\n' || line[i] == '#')
		return (1);
	tmp = ft_grabword(line, i, 0, 1);
	n = string_cleaner(tmp);
	tmp ? free(tmp) : 0;
	n && !is_instruc(n) ? free(n) : 0;
	if (!is_instruc(n))
		return (0);
	struct_tab->instruc = ft_strdup(n);
	i += ft_strlen(n);
	while (line[i] && ft_isblank(line[i]))
		i++;
	start = i;
	while (line[i] && (has_one_param(n) ? !ft_isblank(line[i])
		&& line[i] != '\n' : line[i] != ','))
		i++;
	struct_tab->p1 = ft_strsub(line, start, i - start);
	struct_tab->nb_param = has_one_param(n) ? 1 : struct_tab->nb_param;
	one = has_one_param(n);
	n && has_one_param(n) ? free(n) : 0;
	if (one > 0)
		return (1);
	return (stock_instruc_helper(struct_tab, line, i, n));
}

static void	stock_label(t_line *struct_tab, char *line)
{
	int	i;

	i = 0;
	while (line[i] && line[i] != ':')
		i++;
	struct_tab->label = ft_strsub(line, 0, i);
	while (line[i] && ft_isblank(line[i]))
		i++;
	if (line[i] == '\n' || line[i] == '#' || !line)
		return ;
	stock_instruction(struct_tab, line, i + 1);
}

int			fill_tab_input(char **input, t_line *struct_tab, t_tools *t)
{
	int		i;
	int		start;
	char	*st;
	char	*tmp;

	start = 0;
	st = NULL;
	tmp = NULL;
	i = -1;
	while (++i < ft_tablen(input))
		if (input[i][0] != '.' && input[i][0] != '#')
		{
			t->k = 0;
			while (input[i][t->k] && ft_isblank(input[i][t->k]))
				t->k++;
			start = t->k;
			while (input[i][t->k] && !ft_isblank(input[i][t->k]))
				t->k++;
			st ? free(st) : 0;
			tmp = ft_strsub(input[i], start, t->k - start + 1);
			st = string_cleaner(tmp);
			tmp ? free(tmp) : 0;
			if (st[ft_strlen(st) - 1] == ':')
				stock_label(&struct_tab[t->j], input[i]);
			else if (is_instruc(st))
				stock_instruction(&struct_tab[t->j], input[i], 0);
			t->j += (st[ft_strlen(st) - 1] == ':' || is_instruc(st)) ? 1 : 0;
		}
	st ? free(st) : 0;
	return (1);
}
