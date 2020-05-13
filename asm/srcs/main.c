/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myener <myener@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/11 18:15:35 by myener            #+#    #+#             */
/*   Updated: 2020/05/13 01:41:46 by myener           ###   ########.fr       */
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
	header_fill(header, input, tools);
	// print_struct_tab(struct_tab, len); // DEBUG
	write_to_cor(struct_tab, header, len, fd);
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
	if (fd < 0)
		return (0);
	asm_translator(fd, in_file_content, &tools); // writes the content of in_file in out_file, translated in machinelang.
	// close(fd);
	free(in_file_name);
	free(out_file_name);
	tab_free(in_file_content);
	return (0);
}
