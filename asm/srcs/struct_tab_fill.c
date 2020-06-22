/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_tab_fill.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myener <myener@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/08 16:35:00 by myener            #+#    #+#             */
/*   Updated: 2020/06/22 02:02:23 by myener           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/asm.h"

int		get_param_sz(char *param, int label_size)
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

char	*get_called_label(t_line *tab, int i, int len)
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

int		get_correct_cor_ln(t_line *tab, int i)
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

int		fill_tab_sizes(t_line *tab, int len, t_tools *tools)
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
			tab[i].line_cor_ln += has_coding_byte(tab[i].instruc) ? 1 : 0;
			tab[i].relative_cor_addr = tools->cor_line_counter;
			tab[i].called_label = get_called_label(tab, i, len);
			tools->prog_size += 1;
			tools->prog_size += has_coding_byte(tab[i].instruc) ? 1 : 0;
			tools->prog_size += tab[i].param1_sz + tab[i].param2_sz + tab[i].param3_sz;
		}
		i++;
	}
	return (1);
}

int		stock_instruction(t_line *struct_tab, char *line, int i)
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
	struct_tab->instruc = ft_strdup(instruc_name);
	i += ft_strlen(instruc_name);
	while (line[i] && ft_isblank(line[i]))
		i++;
	start = i;
	while (line[i] && (has_one_param(instruc_name) ? !ft_isblank(line[i]) && line[i] != '\n' : line[i] != ','))
		i++;
	struct_tab->param1 = ft_strsub(line, start, i - start);
	if (has_one_param(instruc_name))
	{
		struct_tab->nb_param = 1;
		free(instruc_name);
		return (1);
	}
	i++;
	while (line[i] && ft_isblank(line[i]))
		i++;
	start = i;
	while (line[i] && (has_two_params(instruc_name) ? !ft_isblank(line[i]) && line[i] != '\n' : line[i] != ','))
		i++;
	struct_tab->param2 = ft_strsub(line, start, i - start);
	if (has_two_params(instruc_name))
	{
		struct_tab->nb_param = 2;
		free(instruc_name);
		return (1);
	}
	i++;
	while (line[i] && ft_isblank(line[i]))
		i++;
	start = i;
	while (line[i] && !ft_isblank(line[i]))
		i++;
	struct_tab->param3 = ft_strsub(line, start, i - start);
	struct_tab->nb_param = 3;
	free(instruc_name);
	return (1);
}

void	stock_label(t_line *struct_tab, char *line)
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

int		fill_tab_input(char **input, t_line *struct_tab, t_header *header, t_tools *tools)
{
	int		i;
	int		j;
	int		k;
	int		len;
	int		start;
	char	*stock;

	(void)header;
	(void)tools;
	(void)struct_tab;
	i = 0;
	j = 0;
	k = 0;
	len = ft_tablen(input);
	start = 0;
	stock = NULL;
	while (i < len)
	{
		if (input[i][0] != '.' && input[i][0] != '#')
		{
			k = 0;
			while (input[i][k] && ft_isblank(input[i][k]))
				k++;
			start = k;
			while (input[i][k] && !ft_isblank(input[i][k]))
				k++;
			stock = ft_strsub(input[i], start, k - start + 1);
			stock = string_cleaner(stock);
			if (stock[ft_strlen(stock) - 1] == ':')
			{
				stock_label(&struct_tab[j], input[i]);
				j++;
			}
			else if (is_instruc(stock))
			{
				stock_instruction(&struct_tab[j], input[i], 0);
				j++;
			}
		}
		i++;
	}
	return (1);
}

int		fill_lonely_labels(t_line *tab, int len)
{
	int i;
	int	j;

	i = 1;
	j = 0;
	while (i < len)
	{
		if (tab[i].label && !tab[i].relative_cor_addr)
		{
			j = i;
			while (j < len && !tab[j].relative_cor_addr)
				j++;
			tab[i].relative_cor_addr = tab[j].relative_cor_addr;
		}
		i++;
	}
	while (i > 0 && !tab[i].label && !tab[i].instruc)
		i--;
	if (tab[i].label && !tab[i].instruc)
	{
		j = i;
		while (j > 0 && !tab[j].instruc)
			j--;
		tab[i].relative_cor_addr = tab[j].relative_cor_addr + tab[j].param1_sz + tab[j].param2_sz + tab[j].param3_sz + has_coding_byte(tab[j].instruc) + 1;
	}
	return (1);
}

int		struct_tab_fill(char **input, t_line *struct_tab, t_header *header, t_tools *tools)
{
	if (!fill_tab_input(input, struct_tab, header, tools))
		return (0);
	if (!fill_tab_sizes(struct_tab, ft_tablen(input), tools))
		return (0);
	if (!fill_lonely_labels(struct_tab, ft_tablen(input)))
		return (0);
	return (1);
}
