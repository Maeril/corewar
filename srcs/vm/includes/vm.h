/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hben-yah <hben-yah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/20 08:09:19 by hben-yah          #+#    #+#             */
/*   Updated: 2020/08/02 15:13:53 by hben-yah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VM_H
# define VM_H

# include <stdlib.h>
# include <stdint.h>
# include <curses.h>
# include <errno.h>
# include <locale.h>
# include <limits.h>
# include "op.h"
# include "libft.h"

/*
** Defines
*/

# define VM_NAME				"Corewar"
# define HEADER_PATH			"./header"

# define VM_OPTIONS				"havVdsc"
# define VM_OP_H				1
# define VM_OP_A				2
# define VM_OP_V				4
# define VM_OP_UP_V				8
# define VM_OP_D				16
# define VM_OP_S				32
# define VM_OP_C				64

/*
** Display
*/

# define OUT_WIDTH			102
# define OUT_WIDTH_MIN		70

# define PAUSE				0
# define RUN				1
# define FW					2
# define STOP				3

# define DFLT_SPEED			50

/*
** Colors
*/

# define P1_COLOR		COLOR_GREEN
# define P2_COLOR		COLOR_BLUE
# define P3_COLOR		COLOR_RED
# define P4_COLOR		COLOR_CYAN
# define P1_FCOLOR		"\033[1;32m"
# define P2_FCOLOR		"\033[1;36m"
# define P3_FCOLOR		"\033[1;35m"
# define P4_FCOLOR		"\033[1;33m"
# define P1_BCOLOR		"\033[0;30;42m"
# define P2_BCOLOR		"\033[0;30;46m"
# define P3_BCOLOR		"\033[0;30;45m"
# define P4_BCOLOR		"\033[0;30;43m"
# define ERR_COLOR		99
# define NORMAL_COLOR	100
# define RCOLOR			256
# define WCOLOR			128

/*
** Structures
*/

typedef struct			s_arg
{
	t_arg_type		type;
	uint8_t			reg;
	int				index;
	uintmax_t		val;
}						t_arg;

typedef struct			s_buff
{
	char	*str;
	size_t	len;
	size_t	max_len;
}						t_buff;

typedef struct			s_champ
{
	int				id;
	int				number;
	char			*file;
	t_header		header;
	int				alive;
	int				n_procs;
	int				last_live;
	int				cur_lives;
	int				last_lives;
	unsigned char	prog[CHAMP_MAX_SIZE];
	t_buff			aff;
	struct s_champ	*next;
}						t_champ;

typedef struct			s_proc
{
	int					id;
	int					number;
	int					prev_pc;
	int					pc;
	int					oc;
	char				carry;
	int					lives;
	int					last_live;
	int					sleep;
	intmax_t			regs[REG_NUMBER];
	t_op				*op;
	t_champ				*champ;
	struct s_proc		*next;
}						t_proc;

typedef struct			s_box
{
	int					row;
	int					col;
	int					x;
	int					y;
}						t_box;

typedef struct			s_display
{
	int					run;
	int					speed;
	int					el_per_line;
	t_box				head;
	t_box				field;
	t_box				info;
	t_box				leg;
	t_box				out;
	WINDOW				*wfield;
	WINDOW				*winfo;
	WINDOW				*wleg;
	WINDOW				*wout;
}						t_display;

typedef struct			s_cell
{
	unsigned char		color;
	unsigned char		modified;
	unsigned char		live;
	unsigned char		reverse;
	int					cycle;
}						t_cell;

typedef struct			s_vm
{
	char				**av;
	int					ac;
	int					options;
	int					option_nb;
	int					dump;
	int					cycle;
	int					cycle_ctd;
	int					cycle_to_die;
	int					checks;
	int					goto_cycle;
	int					nbr_live;
	int					max_checks;
	int					total_lives;
	int					lives;
	int					last_live;
	char				*last_name;
	t_champ				*last_live_champ;
	unsigned char		field[MEM_SIZE];
	t_cell				cells[MEM_SIZE];
	int					n_champs;
	t_champ				*champ;
	int					id_procs;
	int					n_procs;
	t_proc				*proc;
	t_display			display;
	char				*err;
}						t_vm;

extern void				(*g_op_func_tab[18])(t_vm *, t_proc *);
extern char				*g_base;

typedef void			(*t_operation_code)(t_vm *vm, t_proc *ps);

/*
** Prototypes
*/

int						read_champions(t_vm *vm);
void					set_carry(t_proc *p, intmax_t value);
void					move_pc_through_args(t_proc *p, t_arg *args, t_op *op);
int						get_address(t_proc *p, int index);
int						move_pc(t_proc *p, int i);
uintmax_t				read_field(t_vm *vm, t_proc *p, size_t size);
uintmax_t				read_field_at(t_vm *vm, int i, size_t size);
void					read_arg(t_vm *vm, t_proc *p, t_arg *arg);
void					read_val(t_vm *vm, t_proc *p, t_arg *arg);
void					set_reg_val(t_proc *p, int reg, uintmax_t val);
uintmax_t				get_reg_val(t_proc *p, int reg);
int						check_regs(t_arg *args);
void					set_args_types(t_arg *args, unsigned char ocp);
void					write_field_at(t_vm *vm, int i, intmax_t val,
															size_t size);
void					write_val(t_vm *vm, t_proc *p, t_arg arg);
void					init_vm(t_vm *vm);
void					init_proc(t_vm *vm, t_champ *champ, size_t pc);
void					init_procs(t_vm *vm);
void					run_vm(t_vm *vm);
void					exit_vm(t_vm *vm, char *details, int perr);
void					declare_winner(t_vm *vm);
int						main(int ac, char **av);
void					check_procs(t_vm *vm);
void					exec_operation(t_vm *vm, t_proc *p);
void					set_next_operation(t_vm *vm, t_proc *p);
void					exec_procs(t_vm *vm);
void					operate_or(t_vm *vm, t_proc *p);
void					operate_zjmp(t_vm *vm, t_proc *p);
void					operate_lfork(t_vm *vm, t_proc *p);
void					operate_sti(t_vm *vm, t_proc *p);
void					operate_fork(t_vm *vm, t_proc *p);
void					operate_live(t_vm *vm, t_proc *p);
void					operate_xor(t_vm *vm, t_proc *p);
void					operate_ldi(t_vm *vm, t_proc *p);
void					operate_and(t_vm *vm, t_proc *p);
void					operate_st(t_vm *vm, t_proc *p);
void					operate_aff(t_vm *vm, t_proc *p);
void					operate_lld(t_vm *vm, t_proc *p);
void					operate_lldi(t_vm *vm, t_proc *p);
void					operate_add(t_vm *vm, t_proc *p);
void					operate_sub(t_vm *vm, t_proc *p);
void					operate_ld(t_vm *vm, t_proc *p);
void					put_ctd_change(t_vm *vm);
void					put_move(t_vm *vm, t_proc *p);
void					put_op(t_vm *vm, t_proc *p);
void					dump_memory(t_vm *vm);
int						printer(t_vm *vm, int force, const char *str, ...);
void					print_coords(t_vm *vm, int force, int addr);
void					put_arg(t_vm *vm, int force, t_arg arg);
void					put_cycle(t_vm *vm);
void					put_alive(t_vm *vm, t_champ *c);
void					put_kill_pc(t_vm *vm, t_proc *p);
void					put_contestants(t_vm *vm);
void					put_champion(t_vm *vm, t_champ *c);
void					del_vm(t_vm *vm);
void					del_proc(t_proc **ps);
void					del_proc_lst(t_proc **lst);
t_proc					*insert_proc(t_vm *vm, t_proc *new, int n_champ);
t_proc					*fork_proc(t_vm *vm, t_proc *p);
void					del_champ(t_champ **champ);
void					del_champ_lst(t_champ **lst);
t_champ					*get_champ(t_vm *vm, int number);
t_champ					*get_champ_max_lives(t_vm *vm);
t_champ					*get_champ_survivor(t_vm *vm);
t_proc					*new_proc(t_vm *vm);
int						invalid_file_error(void);
int						file_not_found_error(void);
int						put_usage(void);
int						already_attributed_number_error(void);
int						n_arg_error(void);
int						invalid_option_error(char arg);
int						cycle_arg_error(void);
int						no_champion_error(void);
int						too_many_champions_error(void);
int						missing_champion_error(void);
int						champion_size_too_big(void);
int						check_champion_number(t_vm *vm, int number);
int						parse_champion(t_vm *vm, int number, char *file);
void					champ_lst_rev(t_champ **alst);
int						check_vm(t_vm *vm);
int						handle_arguments(t_vm *vm, int ac, char **av);
int						parse_arguments(t_vm *vm, int ac, char **av);
int						parse_options(int *options, char *arg);
void					display_colrow(t_display *d);
void					display_resize(t_vm *vm);
void					init_boxes(t_display *d);
void					init_windows(t_vm *vm, t_display *d);
void					init_visualizer(t_vm *vm);
void					dislay_player_name(t_vm *vm, int *y, int x, t_champ *c);
void					display_player_id(t_vm *vm, int *y, int x,
														unsigned int hex);
void					display_players_infos(t_vm *vm, int *y, int x);
void					display_player_infos(t_vm *vm, int *y, int x,
															t_champ *c);
void					display_info(t_vm *vm);
void					display_borders(t_display *d);
void					reset_windows(t_display *display);
void					reset_visualizer(t_vm *vm);
void					display_current_live_breakdown(t_vm *vm, int *y, int x);
void					display_last_live_breakdown(t_vm *vm, int *y, int x);
void					display_refresh(t_vm *vm);
void					display_move_pc(t_vm *vm, t_proc *p);
void					display_kill_pc(t_vm *vm, t_proc *p);
void					display_header(t_vm *vm);
void					display_winner(t_vm *vm);
void					display_end_loop(t_vm *vm);
void					display_legend(t_vm *vm);
void					visualizer_handle_events(t_vm *vm);
void					visualizer_refresh_events(t_vm *vm);
void					display_field(t_vm *vm);
int						getkey(void);
void					visualizer_handle_keys(t_vm *vm, int key);
void					init_colors(void);
int						get_champion_color(t_vm *vm, int reg);
void					display_color(t_vm *vm, t_proc *p, int index, int size);
int						check_args_types(t_op *op, t_arg *args);
int						count_champs_alive(t_vm *vm);

#endif
