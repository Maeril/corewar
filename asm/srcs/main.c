/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myener <myener@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/11 18:15:35 by myener            #+#    #+#             */
/*   Updated: 2020/05/18 01:22:20 by myener           ###   ########.fr       */
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

void	print_struct_tab(line_t *struct_tab, int len) // DEBUG ONLY
{
	int	i;

	i = 0;
	// len = 5; // TEST
	while (i < len)
	{
		struct_tab[i].label ? ft_printf("label = %s \n", struct_tab[i].label) : 0;
		struct_tab[i].instruc ? ft_printf("instruc = %s \n", struct_tab[i].instruc) : 0;
		ft_printf("param1 = %s \n", struct_tab[i].param1);
		struct_tab[i].param2 ? ft_printf("param2 = %s \n", struct_tab[i].param2) : 0;
		struct_tab[i].param3 ? ft_printf("param3 = %s \n", struct_tab[i].param3) : 0;
		// ft_printf("nb_params = %d \n", struct_tab[i].nb_param);
		// ft_printf("param1_sz = %d \n", struct_tab[i].param1_sz);
		// ft_printf("param2_sz = %d \n", struct_tab[i].param2_sz);
		// ft_printf("param3_sz = %d \n", struct_tab[i].param3_sz);
		// ft_printf("line_cor_length = %d \n", struct_tab[i].line_cor_ln);
		// ft_printf("called_label = %s \n", struct_tab[i].called_label);
		// ft_printf("relative cor address = %d \n", struct_tab[i].relative_cor_addr);
		ft_putstr("_________\n");
		i++;
	}
}

void	header_printer_debug(header_t *header) // DEBUG ONLY
{
	ft_printf("comment = %s\n", header->comment);
	ft_printf("magic = %x\n", header->magic);
	ft_printf("prog name = %s\n", header->prog_name);
	ft_printf("prog size = %x\n", header->prog_size);
}

int		asm_translator(int fd, char **input, tools_t *tools) // fd = fd du .cor
{
	header_t	*header;
	line_t		*struct_tab;

	if (!(header = malloc(sizeof(header_t) * 1)))
		return (0);
	if (!(struct_tab = malloc(sizeof(line_t) * ft_tablen(input))))
		return (0);
	asm_header_init(header);
	asm_struct_tab_init(struct_tab, ft_tablen(input));
	if (!struct_tab_fill(input, struct_tab, header, tools))
		return (0);
	header_fill(header, input, tools);
	// header_printer_debug(header); // DEBUG
	// print_struct_tab(struct_tab, ft_tablen(input)); // DEBUG
	if (!write_to_cor(struct_tab, header, ft_tablen(input), fd))
		return (0);
	return (1);
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
	if ((fd = open(file_name, O_RDONLY)) < 0)
		return (NULL);
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
	tools_t	tools;
	char	*in_file_name;
	char	*out_file_name;
	char	**in_file_content;

	asm_tools_init(&tools);
	if (ac < 2 || (av[1] && (!(av[1][ft_strlen(av[1]) - 1] == 's'
		&& av[1][ft_strlen(av[1]) - 2] == '.'))))
		return (usage_output()); // temporary error output
	if (!(in_file_content = get_file_content(in_file_name = ft_strdup(av[1])))) // seems to be working
		return (error_output());
	out_file_name = ft_strsub(in_file_name, 0, ft_strlen(in_file_name) - 1); //copies input file name except "s"; "file.s" becomes "file."
	out_file_name = ft_free_join(out_file_name, "cor"); // adds "cor" extension to file name; "file." becomes "file.cor"
	if ((fd = open(out_file_name, O_WRONLY | O_CREAT)) < 0)
		return (error_output());
	if (!asm_translator(fd, in_file_content, &tools)) // writes the content of in_file in out_file, translated in machinelang.
		return (error_output());
	close(fd);
	in_file_name ? free(in_file_name) : 0;
	out_file_name ? free(out_file_name) : 0;
	in_file_content? tab_free(in_file_content) : 0;
	return (0);
}
