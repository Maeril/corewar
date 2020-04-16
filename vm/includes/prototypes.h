/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prototypes.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hben-yah <hben-yah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/16 20:26:22 by hben-yah          #+#    #+#             */
/*   Updated: 2020/04/16 20:26:22 by hben-yah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PROTOTYPES_H
# define PROTOTYPES_H

/*
** Prototypes
*/


int				read_champions(t_vm *vm);
void			set_carry(t_proc *p, intmax_t value);
void			move_pc_through_args(t_proc *p, t_arg *args, t_op *op);
int				get_address(t_proc *p, int index);
int				move_pc(t_proc *p, int i);
uintmax_t			read_field(t_vm *vm, t_proc *p, size_t size);
uintmax_t			read_field_at(t_vm *vm, int i, size_t size);
void			read_arg(t_vm *vm, t_proc *p, t_arg *arg);
void			read_val(t_vm *vm, t_proc *p, t_arg *arg);
void			set_reg_val(t_proc *p, int reg, uintmax_t val);
uintmax_t			get_reg_val(t_proc *p, int reg);
int				check_regs(t_arg *args);
void			set_args_types(t_arg *args, unsigned char ocp);
void			write_field_at(t_vm *vm, int i, intmax_t val, size_t size);
void			write_val(t_vm *vm, t_proc *p, t_arg arg);
void			init_vm(t_vm *vm);
void			init_proc(t_vm *vm, t_champ *champ, size_t pc);
void			init_procs(t_vm *vm);
void			run_vm(t_vm *vm);
void			exit_vm(t_vm *vm, char *details, int perr);
void			declare_winner(t_vm *vm);
int				main(int ac, char **av);
void			check_procs(t_vm *vm);
void			exec_operation(t_vm *vm, t_proc *p);
void			set_next_operation(t_vm *vm, t_proc *p);
void			exec_procs(t_vm *vm);
void			operate_or(t_vm *vm, t_proc *p);
void			operate_zjmp(t_vm *vm, t_proc *p);
void			operate_lfork(t_vm *vm, t_proc *p);
void			operate_sti(t_vm *vm, t_proc *p);
void			operate_fork(t_vm *vm, t_proc *p);
void			operate_live(t_vm *vm, t_proc *p);
void			operate_xor(t_vm *vm, t_proc *p);
void			operate_ldi(t_vm *vm, t_proc *p);
void			operate_and(t_vm *vm, t_proc *p);
void			operate_st(t_vm *vm, t_proc *p);
void			operate_aff(t_vm *vm, t_proc *p);
void			operate_lld(t_vm *vm, t_proc *p);
void			operate_lldi(t_vm *vm, t_proc *p);
void			operate_add(t_vm *vm, t_proc *p);
void			operate_sub(t_vm *vm, t_proc *p);
void			operate_ld(t_vm *vm, t_proc *p);
void			put_ctd_change(t_vm *vm);
void			put_move(t_vm *vm, t_proc *p);
void			put_op(t_vm *vm, t_proc *p);
void			dump_memory(t_vm *vm);
int				printer(t_vm *vm, int force, const char *str, ...);
void			print_coords(t_vm *vm, int force, int addr);
void			put_arg(t_vm *vm, int force, t_arg arg);
void			put_cycle(t_vm *vm);
void			put_alive(t_vm *vm, t_champ *c);
void			put_kill_pc(t_vm *vm, t_proc *p);
void			put_contestants(t_vm *vm);
void			put_champion(t_vm *vm, t_champ *c);
void			del_vm(t_vm *vm);
void			del_proc(t_proc **ps);
void			del_proc_lst(t_proc **lst);
t_proc			*insert_proc(t_vm *vm, t_proc *new, int n_champ);
t_proc			*fork_proc(t_vm *vm, t_proc *p);
void			del_champ(t_champ **champ);
void			del_champ_lst(t_champ **lst);
t_champ			*get_champ(t_vm *vm, int number);
t_champ			*get_champ_max_lives(t_vm *vm);
t_champ			*get_champ_survivor(t_vm *vm);
t_proc			*new_proc(t_vm *vm);
int				invalid_file_error(void);
int				file_not_found_error(void);
int				put_usage(void);
int				already_attributed_number_error(void);
int				n_arg_error(void);
int				invalid_option_error(char arg);
int				cycle_arg_error(void);
int				no_champion_error(void);
int				too_many_champions_error(void);
int				missing_champion_error(void);
int				champion_size_too_big(void);
int				check_champion_number(t_vm *vm, int number);
int				parse_champion(t_vm *vm, int number, char *file);
void			champ_lst_rev(t_champ **alst);
int				check_vm(t_vm *vm);
int				handle_arguments(t_vm *vm, int ac, char **av);
int				parse_arguments(t_vm *vm, int ac, char **av);
int				parse_options(int *options, char *arg);
void			display_colrow(t_display *d);
void			display_resize(t_vm *vm);
void			init_boxes(t_display *d);
void			init_windows(t_vm *vm, t_display *d);
void			init_visualizer(t_vm *vm);
void			dislay_player_name(t_vm *vm, int *y, int x, t_champ *c);
void			display_player_id(t_vm *vm, int *y, int x, unsigned int hex);
void			display_player_infos(t_vm *vm, int *y, int x);
void			display_info(t_vm *vm);
void			display_borders(t_display *d);
void			reset_windows(t_display *display);
void			reset_visualizer(t_vm *vm);
void			display_current_live_breakdown(t_vm *vm, int *y, int x);
void			display_last_live_breakdown(t_vm *vm, int *y, int x);
void			display_refresh(t_vm *vm);
void			display_move_pc(t_vm *vm, t_proc *p);
void			display_kill_pc(t_vm *vm, t_proc *p);
void			display_header(t_vm *vm);
void			display_winner(t_vm *vm);
void			display_end_loop(t_vm *vm);
void			display_legend(t_vm *vm);
void			visualizer_handle_events(t_vm *vm);
void			visualizer_refresh_events(t_vm *vm);
void			display_field(t_vm *vm);
int				getkey(void);
void			visualizer_handle_keys(t_vm *vm, int key);
void			init_colors(void);
int				get_champion_color(t_vm *vm, int reg);
void			display_color(t_vm *vm, t_proc *p, int index, int size);

#endif
