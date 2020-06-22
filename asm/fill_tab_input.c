/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_tab_input.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myener <myener@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/23 01:06:21 by myener            #+#    #+#             */
/*   Updated: 2020/06/23 01:50:12 by myener           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/asm.h"

static int		stock_instruc_helper(t_line *s, char *line, int i, char *n)
{
	int	start;

	while (line[i] && ft_isblank(line[i]))
		i++;
	start = i;
	while (line[i] && (has_two_params(n) ? !ft_isblank(line[i])
		&& line[i] != '\n' : line[i] != ','))
		i++;
	s->param2 = ft_strsub(line, start, i - start);
	if (has_two_params(n))
	{
		s->nb_param = 2;
		n ? free(n) : 0;
		return (1);
	}
	i++;
	while (line[i] && ft_isblank(line[i]))
		i++;
	start = i;
	while (line[i] && !ft_isblank(line[i]))
		i++;
	s->param3 = ft_strsub(line, start, i - start);
	s->nb_param = 3;
	n ? free(n) : 0;
	return (1);
}

static int		stock_instruction(t_line *s, char *line, int i)
{
	int		start;
	char	*instruc_name;

	while (line[i] && ft_isblank(line[i]))
		i++;
	if (line[i] == '\n' || line[i] == '#')
		return (1);
	instruc_name = ft_grabword(line, i, 0, 1);
	instruc_name = string_cleaner(instruc_name);
	if (!is_instruc(instruc_name))
		return (0);
	s->instruc = ft_strdup(instruc_name);
	i += ft_strlen(instruc_name);
	while (line[i] && ft_isblank(line[i]))
		i++;
	start = i;
	while (line[i] && (has_one_param(instruc_name) ? !ft_isblank(line[i]) && line[i] != '\n' : line[i] != ','))
		i++;
	s->param1 = ft_strsub(line, start, i - start);
	s->nb_param = has_one_param(instruc_name) ? 1 : s->nb_param;
	has_one_param(instruc_name) ? free(instruc_name) : 0;
	if (has_one_param(instruc_name))
		return (1);
	i++;
	return (stock_instruc_helper(s, line, i, instruc_name));
}

static void		stock_label(t_line *struct_tab, char *line)
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

int				fill_tab_input(char **in, t_line *s, t_header *h, t_tools *t)
{
	int		i;
	int		start;
	char	*st;

	start = 0;
	st = NULL;
	i = -1;
	while (++i < t->tablen)
		if (in[i][0] != '.' && in[i][0] != '#')
		{
			t->k = 0;
			while (in[i][t->k] && ft_isblank(in[i][t->k]))
				t->k++;
			start = t->k;
			while (in[i][t->k] && !ft_isblank(in[i][t->k]))
				t->k++;
			st = ft_strsub(in[i], start, t->k - start + 1);
			st = string_cleaner(st);
			if (st[ft_strlen(st) - 1] == ':')
				stock_label(&s[t->j], in[i]);
			else if (is_instruc(st))
				stock_instruction(&s[t->j], in[i], 0);
			t->j += st[ft_strlen(st) - 1] == ':' || is_instruc(st) ? 1 : 0;
		}
	return (1);
}
