/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_tab_input.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myener <myener@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/23 01:06:21 by myener            #+#    #+#             */
/*   Updated: 2020/07/01 05:57:26 by myener           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/asm.h"

static int	stock_instruc_helper(t_line *struct_tab, char *line, int i, char *n)
{
	int	start;

	while (line[i] && ft_isblank(line[i]))
		i++;
	start = i;
	while (line[i] && (has_two_params(n) ? !ft_isblank(line[i])
		&& line[i] != '\n' : line[i] != ','))
		i++;
	struct_tab->p2 = ft_strsub(line, start, i - start);
	struct_tab->nb_param = has_two_params(n) ? 2 : struct_tab->nb_param;
	if (has_two_params(n))
		return (stock_instruct_clean_free(n, 1));
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

static int	stock_instruction(t_line *struct_tab, char *line, int i, t_tools *t)
{
	char	*n;
	char	*tmp;

	while (line[i] && ft_isblank(line[i]))
		i++;
	if (line[i] == '\n' || line[i] == '#')
		return (1);
	tmp = ft_grabword(line, i, 0, 1);
	n = string_cleaner(tmp);
	tmp ? free(tmp) : 0;
	if (!is_instruc(n))
		return (stock_instruct_clean_free(n, 0));
	struct_tab->instruc = ft_strdup(n);
	i += ft_strlen(n);
	while (line[i] && ft_isblank(line[i]))
		i++;
	t->start = i;
	while (line[i] && (has_one_param(n) ? !ft_isblank(line[i])
		&& line[i] != '\n' : line[i] != ','))
		i++;
	struct_tab->p1 = ft_strsub(line, t->start, i - t->start);
	struct_tab->nb_param = has_one_param(n) ? 1 : struct_tab->nb_param;
	if (has_one_param(n))
		return (stock_instruct_clean_free(n, 1));
	return (stock_instruc_helper(struct_tab, line, i + 1, n));
}

static void	stock_label(t_line *struct_tab, char *line, t_tools *t)
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
	stock_instruction(struct_tab, line, i + 1, t);
}

char		*fill_tab_input_helper(int i, char **input, t_tools *t)
{
	int		start;
	char	*tmp;

	start = 0;
	tmp = NULL;
	t->k = 0;
	while (input[i][t->k] && ft_isblank(input[i][t->k]))
		t->k++;
	start = t->k;
	while (input[i][t->k] && !ft_isblank(input[i][t->k]))
		t->k++;
	tmp = ft_strsub(input[i], start, t->k - start + 1);
	return (tmp);
}

int			fill_tab_input(char **input, t_line *struct_tab, t_tools *t)
{
	int		i;
	char	*st;
	char	*tmp;

	st = NULL;
	tmp = NULL;
	i = -1;
	while (++i < ft_tablen(input))
		if (input[i][0] != '\n' && input[i][0] != '.' && input[i][0] != '#')
		{
			tmp = fill_tab_input_helper(i, input, t);
			st ? free(st) : 0;
			st = string_cleaner(tmp);
			tmp ? free(tmp) : 0;
			if (st[ft_strlen(st) - 1] == ':')
				stock_label(&struct_tab[t->j], input[i], t);
			else if (is_instruc(st))
				stock_instruction(&struct_tab[t->j], input[i], 0, t);
			t->j += (st[ft_strlen(st) - 1] == ':' || is_instruc(st)) ? 1 : 0;
		}
	st ? free(st) : 0;
	return (1);
}
