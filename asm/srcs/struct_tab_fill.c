/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_tab_fill.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myener <myener@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/08 16:35:00 by myener            #+#    #+#             */
/*   Updated: 2020/06/21 05:27:04 by myener           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/asm.h"

int		get_param_sz(char *param, int label_size)
{
	if (param[0] == 'r') // if register
		return (1);
	else if (param[0] == '%') // if direct
	{
		return (label_size == 1 ? 2 : 4);
	}
	else if (param[0] == ':' || (ft_atoi(param) >= INT_MIN && ft_atoi(param) <= INT_MAX)) // if indirect
		return (2);
	return (0);
}

char	*get_called_label(line_t *tab, int i, int len) // in which we assume only one label is called per line
{
	int		j;
	int		start;
	char	*label;
	char	*param;

	param = NULL;
	if (tab[i].param1 && tab[i].param1_sz > 1) // if param exists and isn't a register
		param = ft_strdup(tab[i].param1);
	else if (tab[i].param2 && tab[i].param2_sz > 1)
		param = ft_strdup(tab[i].param2);
	else if (tab[i].param3 && tab[i].param3_sz > 1)
		param = ft_strdup(tab[i].param3);
	else
		return (NULL); // else it means there only are registers, so no possible called label, so return.
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
			// free (param);
			return (is_legit_label(label, tab, len) ? label : NULL);
		}
		j++;
	}
	// param ? free (param) : 0;
	return (NULL);
}

int		get_correct_cor_ln(line_t *tab, int i)
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

void	check_cor_addr(line_t *tab, int len) // DEBUG
{
	int i;

	i = 0;
	while (i < len)
	{
		ft_printf("label = %s, instruc = %s, cor addr = %d\n", tab[i].label, tab[i].instruc, tab[i].relative_cor_addr);
		i++;
	}
}

int		fill_tab_sizes(line_t *tab, int len, tools_t *tools)
{
	int	i;
	int nb;
	int	l;

	i = 0;
	nb = 0;
	l = 0;
	while (i < len) // let's go through the structure array.
	{
		if (tab[i].instruc) // if node contains an instruc, we've got sizes to compute.
		{
			l = has_label_size(tab[i].instruc);
			nb = tab[i].nb_param;
			tools->cor_line_counter += get_correct_cor_ln(tab, i); // needs vetting. 27052020 update: yes the fuck it does. 01062020 update: calm down guys, ive edited the ternary. 19062020 update: well you fucked up somewhere because it's STILL NOT WORKING
			// ft_printf("counter for instruc %s = %d\n", tab[i].instruc, tools->cor_line_counter);
			tab[i].param1_sz = get_param_sz(tab[i].param1, l);
			// ft_printf("param1 = %s, param1 size = %d\n", tab[i].param1, tab[i].param1_sz);
			tab[i].param2_sz = nb == 1 ? 0 : get_param_sz(tab[i].param2, l);
			// ft_printf("param2 = %s, param2 size = %d\n", tab[i].param2, tab[i].param2_sz);
			tab[i].param3_sz = nb == 3 ? get_param_sz(tab[i].param3, l) : 0;
			// ft_printf("param3 = %s, param3 size = %d\n\n", tab[i].param3, tab[i].param3_sz);
			tab[i].line_cor_ln = tab[i].param1_sz + tab[i].param2_sz + tab[i].param3_sz + 1; // +1 for the opcode (size of 1)
			tab[i].line_cor_ln += has_coding_byte(tab[i].instruc) ? 1 : 0; // one more +1 if there's a coding byte (only 4 instrucs have one)
			tab[i].relative_cor_addr = tools->cor_line_counter;
			// ft_printf("relative cor addr = %d (all precedent params sizes + opcode, coding byte = %d)\n\n", tab[i].relative_cor_addr, has_coding_byte(tab[i].instruc));
			// ft_printf("tab[%d].label = %s\n", i, tab[i].label);
			// ft_printf("tab[%d].param1 = >%s<\n", i, tab[i].param1);
			tab[i].called_label = get_called_label(tab, i, len);
			// ft_printf("tab[%d].called_label = %s\n", i, tab[i].called_label);
			// ft_printf("label = %s && called label = %s\n", tab[i].label, tab[i].called_label);
			// ft_printf("line_cor_ln = %d\n\n", tab[i].line_cor_ln);
			tools->prog_size += 1; // 1 for the opcode (1 byte)
			tools->prog_size += has_coding_byte(tab[i].instruc) ? 1 : 0; // for the optional coding byte (1 byte too)
			tools->prog_size += tab[i].param1_sz + tab[i].param2_sz + tab[i].param3_sz; // additions up all sizes to get prog size;
		}
		i++;
	}
	// ft_printf("progsize = %d\n", tools->prog_size);
	return (1);
}

int		stock_instruction(line_t *struct_tab, char *line, int i)
{
	int		start;
	char	*instruc_name;
	// char	*instruc_name_2;

	// GRAB INSTRUCTION NAME
	while (line[i] && ft_isblank(line[i]))
		i++;
	if (line[i] == '\n' || line[i] == '#')
		return (1);
	instruc_name = ft_grabword(line, i, 0, 1, 0);
	// ft_printf("line %d, instruc_name = >%s<\n", i, instruc_name);
	instruc_name = string_cleaner(instruc_name);
	// ft_printf("line %d, instruc_name = >%s<\n\n", i, instruc_name);
	if (!is_instruc(instruc_name))
	{
		// ft_printf("ERROR, instruc name '%s' on line %d isn't an actual instruction.\n", instruc_name, i);
		return(error_output()) ; // ERROR OUTPUT
	}
	struct_tab->instruc = ft_strdup(instruc_name);
	// GRAB PARAM 1
	i += ft_strlen(instruc_name);
	// ft_printf("line = %s, i = %d\n", line, i);
	while (line[i] && ft_isblank(line[i]))
		i++;
	// ft_printf("i = %d\n", i);
	start = i;
	while (line[i] && (has_one_param(instruc_name) ? !ft_isblank(line[i]) && line[i] != '\n' : line[i] != ','))
		i++;
	struct_tab->param1 = ft_strsub(line, start, i - start);
	// ft_printf("param1 = %s\n", struct_tab->param1);
	if (has_one_param(instruc_name))
	{
		struct_tab->nb_param = 1;
		free(instruc_name);
		return (1);
	}
	// GRAB PARAM 2
	i++;
	while (line[i] && ft_isblank(line[i]))
		i++;
	start = i;
	while (line[i] && (has_two_params(instruc_name) ? !ft_isblank(line[i]) && line[i] != '\n' : line[i] != ','))
		i++;
	struct_tab->param2 = ft_strsub(line, start, i - start);
	// ft_printf("param2 = %s\n", struct_tab->param2);
	if (has_two_params(instruc_name))
	{
		struct_tab->nb_param = 2;
		free(instruc_name);
		return (1);
	}
	// GRAB PARAM 3
	i++;
	while (line[i] && ft_isblank(line[i]))
		i++;
	start = i;
	while (line[i] && !ft_isblank(line[i]))
		i++;
	struct_tab->param3 = ft_strsub(line, start, i - start);
	// ft_printf("param3 = %s\n", struct_tab->param3);
	struct_tab->nb_param = 3;
	free(instruc_name);
	return (1);
}

void	stock_label(line_t *struct_tab, char *line)
{
	int	i;

	i = 0;

	while (line[i] && line[i] !=':')
		i++;
	struct_tab->label = ft_strsub(line, 0, i);
	while (line[i] && ft_isblank(line[i]))
		i++;
	if (line[i] == '\n' || line[i] == '#' || !line) // if the rest of the line doesn't include instructions,
		return ; // then we're done here, return;
	stock_instruction(struct_tab, line, i + 1); // otherwise stock the rest of the line.
}

int		fill_tab_input(char **input, line_t *struct_tab, header_t *header, tools_t *tools)
{
	int		i;
	int		j;
	int		k;
	int		len;
	int		start;
	char	*stock;

	(void)header; // TEST
	(void)tools; // TEST
	(void)struct_tab; // TEST
	i = 0;
	j = 0;
	k = 0;
	len = ft_tablen(input);
	start = 0;
	stock = NULL;
	// ft_printf("tablen de input = %d\n", len);
	while (i < len)
	{
		// ft_printf("i = %d, len = %d\n", i, len);
		// ft_printf("input[%d] = %s", i, input[i]);
		// ft_printf("%s", input[i]);
		if (input[i][0] != '.' && input[i][0] != '#')
		{
			k = 0;
			while (input[i][k] && ft_isblank(input[i][k])) // skip the eventual spaces in the beginning
				k++;
			// if (ft_islownum(input[i][k])) // if the first real thing on the line (i.e. not spaces) is lowercases or a digit
				start = k; // then we mark when it starts
			while (input[i][k] && !ft_isblank(input[i][k])) // go through until you meet a space or the line ends (that one's unlikely)
				k++;
			stock = ft_strsub(input[i], start, k - start + 1);
			stock = string_cleaner(stock);
			if (stock[ft_strlen(stock) - 1] == ':')
			{
				// ft_printf("label input[%d] = %s\n", i, input[i]);
				stock_label(&struct_tab[j], input[i]);//stock label line in struct_tab[j]
				j++;
			}
			else if (is_instruc(stock))
			{
				// ft_printf("instruction input[%d] = %s\n", i, input[i]);
				stock_instruction(&struct_tab[j], input[i], 0);//stock instruction line in struct_tab[j]
				j++;
			}
			// else
			// {
				// ft_printf("situation non gérée !\n");
				// break ; // temporary "if none matches then it's bullshit so ignore" instruction
			// }
			// is_instruc(stock) ? stock
		}
		i++;
	}
	return (1);
}

int		fill_lonely_labels(line_t *tab, int len)
{
	int i;
	int	j;

	i = 1; // and not 0 to jump over the first line of tab, whose relative addr will always be 0.
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

int		struct_tab_fill(char **input, line_t *struct_tab, header_t *header, tools_t *tools)
{
	if (!fill_tab_input(input, struct_tab, header, tools))
		return (0);
	if (!fill_tab_sizes(struct_tab, ft_tablen(input), tools))
		return (0);
	if (!fill_lonely_labels(struct_tab, ft_tablen(input)))
		return (0);
	// check_cor_addr(struct_tab, ft_tablen(input));
	return (1);
}
