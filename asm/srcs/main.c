/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myener <myener@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/11 18:15:35 by myener            #+#    #+#             */
/*   Updated: 2020/04/26 01:07:20 by myener           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/asm.h"

void	name_comment_stock(header_t *header, char *line, t_tools *tools)
{
	int		i;
	int		beg;

	i = 0;
	if (!ft_strncmp(line, NAME_CMD_STRING, 5) && tools->name_filled == 0)
	{
		i = 6;
		while (line[i] && line[i] != '"')
			i++;
		beg = i++; // and not 0 to jump over the ", and also increment i in one line (hopefully);
		while (line[i] && line[i] != '"')
			i++;
		if (i - beg > PROG_NAME_LENGTH)
			return ; // OUTPUT ERROR AND EXIT
		header->prog_name = ft_strsub(line, beg, i - beg + 1);
		// ft_printf("prog_name = %s\n", header->prog_name) // for proofreading only
		tools->name_filled = 1;
	}
	else if (!ft_strncmp(line, COMMENT_CMD_STRING, 8) && tools->com_filled == 0)
	{
		i = 9;
		while (line[i] && line[i] != '"')
			i++;
		beg = i++; // and not 0 to jump over the ", and also increment i in one line (hopefully);
		while (line[i] && line[i] != '"')
			i++;
		if (i - beg > COMMENT_LENGTH)
			return ; // OUTPUT ERROR AND EXIT
		header->comment = ft_strsub(line, beg, i - beg + 1);
		// ft_printf("comment = %s\n", header->comment) // for proofreading only
		tools->com_filled = 1;
	}
	//else, do nothing. gotta check whether encountering >1 name or comment = error.
}

void	stock_instruction(t_line struct_tab, char *line)
{
	int		i;
	int		start;
	char	*instruc_name;

	i = 0;
	while (line[i])
	{
		while (ft_isblank(line[i])) // get past the space(s)
			i++;
		instruc_name = ft_grabword(line, i, 0, 1);
		if (!is_instruc(instruc_name))
			return ; // ERROR OUTPUT
		struct_tab.instruc = ft_strdup(instruc_name);
		// GRAB PARAM 1
		i += ft_strlen(instruc_name);
		while (ft_isblank(line[i]))
			i++;
		start = i;
		while (!(ft_isblank(line[i]) || line[i] != ','))
			i++;
		struct_tab.param1 = ft_strsub(line, start, i - start + 1);
		if (has_one_param(instruc_name))
			break;
		// GRAB PARAM 2
		i++;
		while (ft_isblank(line[i]))
			i++;
		start = i;
		while (!(ft_isblank(line[i]) || line[i] != ','))
			i++;
		struct_tab.param2 = ft_strsub(line, start, i - start + 1);
		if (has_two_params(instruc_name))
			break;
		// GRAB PARAM 3
		i++;
		while (ft_isblank(line[i]))
			i++;
		start = i;
		while (!(ft_isblank(line[i]) || line[i] != ','))
			i++;
		struct_tab.param3 = ft_strsub(line, start, i - start + 1);
	}

	free(instruc_name);
}

void	stock_label(t_line struct_tab, char *line)
{
	
}

void	fill_struct_tab(char **input, t_line *struct_tab, header_t *header,t_tools *tools)
{
	int			i;
	int			j;

	if (!(struct_tab = malloc(sizeof(t_line) * ft_tablen(input))))
		return ;
	if (!(header = malloc(sizeof(header_t) * 1)))
		return ;
	i = 0;
	j = 0;
	while (input[i])
	{
		if (input[i][0] == '.') // if line starts with '.'
			name_comment_stock(header, input[i], tools);//stock name or comment from that line to header (if it's on this line) in the header. otherwise do nothing
		else if ((input[i][0] == '\t' || input[i][0] == ' ')) // if line starts with '\t' or ' '
			stock_instruction(struct_tab[j], input[i]);//stock instruction line in struct_tab[j]
		else if (ft_isalnum(input[i][0])) // if line starts with a number or character
			stock_label(struct_tab[j], input[i]);//stock label line in struct_tab[j]
		i++;
		j++;
	}

}

void	asm_translator(int fd, char **input, t_tools *tools) // fd = fd du .cor
{

	header_t	*header; // here header's still uninitialized
	t_line		*struct_tab;

	asm_header_init(header);
	asm_struct_tab_init(struct_tab);
	fill_struct_tab(input, struct_tab, header, tools);
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
	content = ft_strsplit(stock, '\0');
	ft_strdel(&stock);
	return (content);
}

int		main(int ac, char **av)
{
	int		fd;
	// int		test_10;
	t_tools	tools;
	char	*in_file_name;
	char	*out_file_name;
	char	**in_file_content;

	// test_10 = 10;
	asm_tools_init(&tools);
	if (ac < 2)
		return (-1); // temporary error output
	in_file_name = ft_strdup(av[1]); // copies input file's name for later
	in_file_content = get_file_content(in_file_name);
	out_file_name = ft_strsub(in_file_name, 0, ft_strlen(in_file_name) - 1); //copies input file name except "s"; "file.s" becomes "file."
	out_file_name = ft_free_join(out_file_name, "cor"); // adds "cor" extension to file name; "file." becomes "file.cor"
	ft_printf("out_file_name = %s\n", out_file_name);
	fd = open(out_file_name, O_WRONLY | O_CREAT); // opens out_file: it doesn't exists, so it creates it. open to WRITE in it.
	// write(fd, &test_10, sizeof(int)); // test for displaying in hex (to handle WAY LATER)
	asm_translator(fd, in_file_content, &tools); // writes the content of in_file in out_file, translated in machinelang.
	// close(fd);
	free(in_file_name);
	free(out_file_name);
	tab_free(in_file_content);
	return (0);
}
