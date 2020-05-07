/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myener <myener@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/11 18:15:35 by myener            #+#    #+#             */
/*   Updated: 2020/05/07 17:55:09 by myener           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/asm.h"

static char	**append_return(char **in)
{
	int		i;

	i = 0;
	while (in[i])
	{
		in[i] = ft_free_join(in[i], "\n");
		i++;
	}
	if (i == 0)
	{
		in ? tab_free(in) : 0;
		return (NULL);
	}
	return (in);
}

void	print_struct_tab(line_t *struct_tab, int len)
{
	int	i;

	i = 0;
	// len = 5; // TEST
	while (i < len)
	{
		ft_printf("label = %s \n", struct_tab[i].label);
		ft_printf("instruc = %s \n", struct_tab[i].instruc);
		ft_printf("param1 = %s \n", struct_tab[i].param1);
		ft_printf("param2 = %s \n", struct_tab[i].param2);
		ft_printf("param3 = %s \n", struct_tab[i].param3);
		ft_printf("nb_params = %d \n", struct_tab[i].nb_param);
		ft_printf("param1_sz = %d \n", struct_tab[i].param1_sz);
		ft_printf("param2_sz = %d \n", struct_tab[i].param2_sz);
		ft_printf("param3_sz = %d \n", struct_tab[i].param3_sz);
		ft_printf("line_cor_length = %d \n", struct_tab[i].line_cor_ln);
		ft_printf("called_label = %s \n", struct_tab[i].called_label);
		ft_printf("relative cor address = %d \n", struct_tab[i].relative_cor_addr);
		ft_putstr("_________\n");
		i++;
	}
}

// void	name_comment_stock(header_t *header, char *line, tools_t *tools)
// {
// 	int		i;
// 	int		beg;

// 	i = 0;
// 	if (!ft_strncmp(line, NAME_CMD_STRING, 5) && tools->name_filled == 0)
// 	{
// 		i = 6;
// 		while (line[i] && line[i] != '"')
// 			i++;
// 		beg = i++; // and not 0 to jump over the ", and also increment i in one line (hopefully);
// 		while (line[i] && line[i] != '"')
// 			i++;
// 		if (i - beg > PROG_NAME_LENGTH)
// 			return ; // OUTPUT ERROR AND EXIT
// 		header->prog_name = ft_strsub(line, beg, i - beg + 1);
// 		// ft_printf("prog_name = %s\n", header->prog_name) // for proofreading only
// 		tools->name_filled = 1;
// 	}
// 	else if (!ft_strncmp(line, COMMENT_CMD_STRING, 8) && tools->com_filled == 0)
// 	{
// 		i = 9;
// 		while (line[i] && line[i] != '"')
// 			i++;
// 		beg = i++; // and not 0 to jump over the ", and also increment i in one line (hopefully);
// 		while (line[i] && line[i] != '"')
// 			i++;
// 		if ((i - beg) > COMMENT_LENGTH)
// 			return ; // OUTPUT ERROR AND EXIT
// 		header->comment = ft_strsub(line, beg, i - beg + 1);
// 		// ft_printf("comment = %s\n", header->comment) // for proofreading only
// 		tools->com_filled = 1;
// 	}
// 	//else, do nothing. gotta check whether encountering >1 name or comment = error.
// }

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

int		is_legit_label(char *label, line_t *tab, int len)
{
	int i;

	i = 0;
	while (i < len)
	{
		if (tab[i].label && !ft_strcmp(label, tab[i].label))
			return (1);
		i++;
	}
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

int		get_opcode(char *instruc)
{
	if (!ft_strcmp(instruc, "live"))
		return (1);
	else if (!ft_strcmp(instruc, "ld"))
		return (2);
	else if (!ft_strcmp(instruc, "st"))
		return (3);
	else if (!ft_strcmp(instruc, "add"))
		return (4);
	else if (!ft_strcmp(instruc, "sub"))
		return (5);
	else if (!ft_strcmp(instruc, "and"))
		return (6);
	else if (!ft_strcmp(instruc, "or"))
		return (7);
	else if (!ft_strcmp(instruc, "xor"))
		return (8);
	else if (!ft_strcmp(instruc, "zjmp"))
		return (9);
	else if (!ft_strcmp(instruc, "ldi"))
		return (10);
	else if (!ft_strcmp(instruc, "sti"))
		return (11);
	else if (!ft_strcmp(instruc, "fork"))
		return (12);
	else if (!ft_strcmp(instruc, "lld"))
		return (13);
	else if (!ft_strcmp(instruc, "lldi"))
		return (14);
	else if (!ft_strcmp(instruc, "lfork"))
		return (15);
	else if (!ft_strcmp(instruc, "aff"))
		return (16);
	return (0);
}

int		get_coding_byte(line_t *tab, int i)
{
	int		j;
	int		counter;
	char	*byte;

	// 1: build coding byte binary from data in struc
	counter = 0;
	byte = ft_strnew(1);
	if (tab[i].param1 > 0)
	{
		if (tab[i].param1[0] == '%') // if yes then it's a direct
			byte = ft_free_join(byte, "10");
		else // else it's: a register if sz = 1, an indirect otherwise.
			byte = ft_free_join(byte, tab[i].param1_sz == 1 ? "01" : "11");
		counter += 2;
	}
	if (tab[i].param2 > 0)
	{
		if (tab[i].param2[0] == '%') // if yes then it's a direct
			byte = ft_free_join(byte, "10");
		else // else it's: a register if sz = 1, an indirect otherwise.
			byte = ft_free_join(byte, tab[i].param2_sz == 1 ? "01" : "11");
		counter += 2;
	}
	if (tab[i].param3 > 0)
	{
		if (tab[i].param3[0] == '%') // if yes then it's a direct
			byte = ft_free_join(byte, "10");
		else // else it's: a register if sz = 1, an indirect otherwise.
			byte = ft_free_join(byte, tab[i].param3_sz == 1 ? "01" : "11");
		counter += 2;
	}
	j = 0;
	while (j < (8 - counter))
	{
		byte = ft_free_join(byte, "0");
		j++;
	}
	return (ft_atoi(base_converter(byte, BIN, DECI)));
}

void	write_param(char *str, int write_size); // TO DO

void	write_to_cor(line_t *tab, int len, int fd)
{
	int i;

	// write_header();
	i = 0;
	(void)fd; //test
	while (i < len)
	{
		if (tab[i].instruc)
		{
			// ft_printf("instruc = %s & get opcode = %d\n", tab[i].instruc, get_opcode(tab[i].instruc));
			ft_putnbr_base_fd(fd, get_opcode(tab[i].instruc), HEXL);
			if (has_coding_byte(tab[i].instruc))
			{
				ft_putnbr_base_fd(fd, get_coding_byte(tab, i), HEXL);
				// ft_putchar_fd(' ', fd); // TEST
			}
			if (tab[i].param1)
				write_param(tab[i].param1, tab[i].param1_sz);
			if (tab[i].param2)
				write_param(tab[i].param2, tab[i].param2_sz);
			if (tab[i].param3)
				write_param(tab[i].param3, tab[i].param3_sz);
		}
		// if (tab[i].called_label)
		i++;
	}
}

void	asm_translator(int fd, char **input, tools_t *tools) // fd = fd du .cor
{
	int			len;
	header_t	*header; // here header's still uninitialized
	line_t		*struct_tab;

	(void)fd; // TEST
	len = ft_tablen(input);
	if (!(header = malloc(sizeof(header_t) * 1)))
		return ;
	if (!(struct_tab = malloc(sizeof(line_t) * len)))
		return ;
	asm_header_init(header);
	asm_struct_tab_init(struct_tab, len);
	// ft_putstr("segfault finder\n");
	fill_tab_input(input, struct_tab, header, tools);
	fill_tab_sizes(struct_tab, len, tools);
	// print_struct_tab(struct_tab, len); // TEST
	write_to_cor(struct_tab, len, fd);
	// parse_struct_tab(fd, struct_tab)
}

char	**get_file_content(char *file_name)
{
	int		i;
	int		fd;
	char	*tmp;
	char	*line;
	char	*stock;
	char	**content;

	i = 0;
	stock = ft_strnew(1);
	fd = open(file_name, O_RDONLY);
	while (get_next_line(fd, &line))
	{
		tmp = line;
		stock = ft_free_join(stock, line);
		stock = ft_free_join(stock, "\n");
		free(tmp);
		i++;
	}
	close(fd);
	content = ft_strsplit(stock, '\n');
	content = append_return(content);
	ft_strdel(&stock);
	return (content);
}

int		main(int ac, char **av)
{
	int		fd;
	// int		test_10;
	tools_t	tools;
	char	*in_file_name;
	char	*out_file_name;
	char	**in_file_content;

	// test_10 = 10;
	// ft_printf("11 en hexa donne %#04x\n", 11);// TEST affichage hexa
	asm_tools_init(&tools);
	if (ac < 2)
		return (-1); // temporary error output
	in_file_name = ft_strdup(av[1]); // copies input file's name for later
	in_file_content = get_file_content(in_file_name);
	out_file_name = ft_strsub(in_file_name, 0, ft_strlen(in_file_name) - 1); //copies input file name except "s"; "file.s" becomes "file."
	out_file_name = ft_free_join(out_file_name, "cor"); // adds "cor" extension to file name; "file." becomes "file.cor"
	// ft_printf("out_file_name = %s\n", out_file_name); // TEST
	fd = open(out_file_name, O_WRONLY | O_CREAT); // opens out_file: it doesn't exists, so it creates it. open to WRITE in it.
	// ft_printf("fd = %d\n", fd)
	// write(fd, &test_10, sizeof(int)); // test for displaying in hex (to handle WAY LATER)
	asm_translator(fd, in_file_content, &tools); // writes the content of in_file in out_file, translated in machinelang.
	// close(fd);
	free(in_file_name);
	free(out_file_name);
	tab_free(in_file_content);
	return (0);
}
