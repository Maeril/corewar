/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myener <myener@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/11 18:15:35 by myener            #+#    #+#             */
/*   Updated: 2020/06/23 21:37:09 by myener           ###   ########.fr       */
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

int			asm_translator(int fd, char **input, t_tools *tools)
{
	t_header	*header;
	t_line		*struct_tab;

	if (!(header = malloc(sizeof(t_header) * 1)))
		return (0);
	if (!(struct_tab = malloc(sizeof(t_line) * ft_tablen(input))))
		return (0);
	ft_bzero(header, sizeof(t_header));
	asm_struct_tab_init(struct_tab, ft_tablen(input));
	if (!struct_tab_fill(input, struct_tab, tools))
	{
		header ? free(header) : 0;
		asm_struct_tab_free(struct_tab, ft_tablen(input));
		return (0);
	}
	header_fill(header, input, tools);
	tools->tablen = ft_tablen(input);
	tools->fd = fd;
	if (!write_to_cor(struct_tab, header, tools))
	{
		header ? free(header) : 0;
		asm_struct_tab_free(struct_tab, ft_tablen(input));
		return (0);
	}
	header ? free(header) : 0;
	asm_struct_tab_free(struct_tab, ft_tablen(input));
	return (1);
}

char		**get_file_content(char *file_name)
{
	int		fd;
	char	*tmp;
	char	*line;
	char	*stock;
	char	**content;

	stock = ft_strnew(1);
	if ((fd = open(file_name, O_RDONLY)) < 0)
		return (NULL);
	while (get_next_line(fd, &line))
	{
		tmp = line;
		stock = ft_free_join(stock, line);
		stock = ft_free_join(stock, "\n");
		tmp ? free(tmp) : 0;
	}
	close(fd);
	content = ft_strsplit(stock, '\n');
	content = append_return(content);
	stock ? ft_strdel(&stock) : 0;
	return (content);
}

int			main(int ac, char **av)
{
	int		fd;
	t_tools	tools;
	char	*in_file_name;
	char	*out_file_name;
	char	**in_file_content;

	asm_tools_init(&tools);
	if (ac < 2 || (av[1] && (!(av[1][ft_strlen(av[1]) - 1] == 's'
		&& av[1][ft_strlen(av[1]) - 2] == '.'))))
		return (usage_output());
	in_file_name = ft_strdup(av[1]);
	if (!(in_file_content = get_file_content(in_file_name)))
	{
		in_file_name ? free(in_file_name) : 0;
		in_file_content ? tab_free(in_file_content) : 0;
		return (error_output());
	}
	out_file_name = ft_strsub(in_file_name, 0, ft_strlen(in_file_name) - 1);
	out_file_name = ft_free_join(out_file_name, "cor");
	fd = open(out_file_name, O_RDWR | O_CREAT, S_IRUSR | S_IRGRP | S_IROTH);
	if (fd < 0)
	{
		in_file_name ? free(in_file_name) : 0;
		out_file_name ? free(out_file_name) : 0;
		in_file_content ? tab_free(in_file_content) : 0;
		return (error_output());
	}
	if (!asm_translator(fd, in_file_content, &tools))
	{
		in_file_name ? free(in_file_name) : 0;
		out_file_name ? free(out_file_name) : 0;
		in_file_content ? tab_free(in_file_content) : 0;
		return (error_output());
	}
	close(fd);
	in_file_name ? free(in_file_name) : 0;
	out_file_name ? free(out_file_name) : 0;
	in_file_content ? tab_free(in_file_content) : 0;
	return (0);
}
