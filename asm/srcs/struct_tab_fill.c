/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_tab_fill.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myener <myener@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/08 16:35:00 by myener            #+#    #+#             */
/*   Updated: 2020/05/08 16:57:55 by myener           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/asm.h"

int		get_param_sz(char *param, int label_size)
{
	if (param[0] == 'r') // if registre
		return (1);
	else if (param[0] == '%') // if direct
		return (label_size  == 1 ? 2 : 4);
	else if (param[0] == ':' || ft_isdigit(param[0])) // if indirect
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
			free (param);
			return (is_legit_label(label, tab, len) ? label : NULL);
		}
		j++;
	}
	param ? free (param) : 0;
	return (NULL);
}

void	fill_tab_sizes(line_t *tab, int len, tools_t *tools)
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
			tools->cor_line_counter += (i > 1 ? tab[i - 1].line_cor_ln : 0); // needs vetting
			tab[i].param1_sz = get_param_sz(tab[i].param1, l);
			tab[i].param2_sz = nb == 1 ? 0 : get_param_sz(tab[i].param2, l);
			tab[i].param3_sz = nb == 3 ? get_param_sz(tab[i].param3, l) : 0;
			tab[i].line_cor_ln = tab[i].param1_sz + tab[i].param2_sz + tab[i].param3_sz + 2; // +2 for the opcode and coding byte (each have a size of 1)
			tab[i].relative_cor_addr = tools->cor_line_counter;
			tab[i].called_label = get_called_label(tab, i, len);
			// ft_printf("label = %s && called label = %s\n", tab[i].label, tab[i].called_label);
		}
		i++;
	}
}

void	stock_instruction(line_t *struct_tab, char *line, int i)
{
	int		start;
	char	*instruc_name;
	// char	*instruc_name_2;

	// GRAB INSTRUCTION NAME
	while (line[i] && ft_isblank(line[i]))
		i++;
	if (line[i] == '\n' || line[i] == '#')
		return ;
	instruc_name = ft_grabword(line, i, 0, 1);
	// ft_printf("instruc_name = >%s<\n", instruc_name);
	instruc_name = ft_strtrim(instruc_name);
	// ft_printf("instruc_name = >%s<\n\n", instruc_name);
	if (!is_instruc(instruc_name))
	{
		ft_printf("ERROR\n");
		return ; // ERROR OUTPUT
	}
	struct_tab->instruc = ft_strdup(instruc_name);
	// GRAB PARAM 1
	i += ft_strlen(instruc_name);
	// ft_printf("line = %s, i = %d\n", line, i);
	while (line[i] && ft_isblank(line[i]))
		i++;
	// ft_printf("i = %d\n", i);
	start = i;
	while (line[i] && line[i] != ',')
		i++;
	struct_tab->param1 = ft_strsub(line, start, i - start + 1);
	// ft_printf("param1 = %s\n", struct_tab->param1);
	if (has_one_param(instruc_name))
	{
		struct_tab->nb_param = 1;
		free(instruc_name);
		return ;
	}
	// GRAB PARAM 2
	i++;
	while (line[i] && ft_isblank(line[i]))
		i++;
	start = i;
	while (line[i] && line[i] != ',')
		i++;
	struct_tab->param2 = ft_strsub(line, start, i - start + 1);
	// ft_printf("param2 = %s\n", struct_tab->param2);
	if (has_two_params(instruc_name))
	{
		struct_tab->nb_param = 2;
		free(instruc_name);
		return ;
	}
	// GRAB PARAM 3
	i++;
	while (line[i] && ft_isblank(line[i]))
		i++;
	start = i;
	while (line[i] && line[i] != ',')
		i++;
	struct_tab->param3 = ft_strsub(line, start, i - start + 1);
	// ft_printf("param3 = %s\n", struct_tab->param3);
	struct_tab->nb_param = 3;
	free(instruc_name);
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

void	fill_tab_input(char **input, line_t *struct_tab, header_t *header, tools_t *tools)
{
	int			i;
	int			j;

	(void)header; // TEST
	(void)tools; // TEST
	i = 0;
	j = 0;
	while (input[i])
	{
		// if (input[i][0] == '.') // if line starts with '.'
			// name_comment_stock(header, input[i], tools);//stock name or comment from that line to header (if it's on this line) in the header. otherwise do nothing
		if ((input[i][0] == '\t' || input[i][0] == ' ')) // if line starts with '\t' or ' '
		{
			// ft_printf("INSTRUC\n");
			stock_instruction(&struct_tab[j], input[i], 0);//stock instruction line in struct_tab[j]
		}
		else if (ft_isalnum(input[i][0])) // if line starts with a number or character
		{
			// ft_printf("LABEL\n");
			stock_label(&struct_tab[j], input[i]);//stock label line in struct_tab[j]
		}
		i++;
		j++;
	}

}
