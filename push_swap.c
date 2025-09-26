/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgomes-d <rgomes-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 18:39:09 by rgomes-d          #+#    #+#             */
/*   Updated: 2025/09/26 20:17:36 by rgomes-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int				check_order(t_meta_ilist *nums);
void			init_sorting(t_core *stack);
int				sorting(t_divides chunck, t_core *stack);
t_all_chunks	create_chuncks(t_divides chunck, t_core *stack);
t_divides		aux_create_chuncks(t_divides chunck, t_chunck w_chunk);
void			print_moves(t_core *core);
t_divides		resolve_mod(t_divides chunck);
void			calculate_move(t_core *core, t_side from, t_side to);

int	main(int argc, char **argv)
{
	t_meta_ilist	*nums;
	t_core			*core;

	if (argc <= 1)
		return (0);
	if (ft_gc_init())
		return (handle_error());
	nums = parsing_args(argv);
	if (!nums)
		return (1);
	if (check_order(nums))
	{
		if (!core_utils())
			return (handle_error());
		core = core_utils();
		init_sorting(core);
	}
	ft_gc_end();
	return (0);
}
void	init_sorting(t_core *stack)
{
	t_divides	main;

	main.num_final = stack->stack_a->size;
	main.num_init = 1;
	main.size = stack->stack_a->size;
	main.w_chunck = ALL;
	main.w_side = TOP_A;
	main.mod = 0;
	sorting(main, stack);
	control_moves(NONE, stack);
}

int	sorting(t_divides chunck, t_core *stack)
{
	t_all_chunks	others;

	if (chunck.size <= 3)
	{
		if (chunck.size == 3)
		{
			calculate_move(stack, chunck.w_side, TOP_A);
			calculate_move(stack, chunck.w_side, TOP_A);
			calculate_move(stack, chunck.w_side, TOP_A);
		}
		else if (chunck.size == 2)
		{
			calculate_move(stack, chunck.w_side, TOP_A);
			calculate_move(stack, chunck.w_side, TOP_A);
		}
		else if (chunck.size == 1)
			calculate_move(stack, chunck.w_side, TOP_A);
		return (0);
	}
	others = create_chuncks(chunck, stack);
	sorting(others.side[HIGHERS], stack);
	sorting(others.side[AVERAGE], stack);
	sorting(others.side[LOWERS], stack);
	return (0);
}

t_all_chunks	create_chuncks(t_divides chunck, t_core *stack)
{
	t_all_chunks	others;
	int				i[2];

	others.side[LOWERS] = aux_create_chuncks(chunck, LOWERS);
	others.side[AVERAGE] = aux_create_chuncks(others.side[LOWERS], AVERAGE);
	others.side[HIGHERS] = aux_create_chuncks(others.side[AVERAGE], HIGHERS);
	i[0] = stack->stack_a->head->r_pos;
	if (chunck.w_side == BOT_A && (i[0] >= chunck.num_init && i[0] <= chunck.num_final))
		chunck.w_side = TOP_A;
	if (stack->stack_b->head)
		i[0] = stack->stack_b->head->r_pos;
	if (chunck.w_side == BOT_B && (i[0] >= chunck.num_init && i[0] <= chunck.num_final))
		chunck.w_side = TOP_B;
	while (chunck.size-- > 0)
	{
		if (chunck.w_side == TOP_A)
			i[0] = stack->stack_a->head->r_pos;
		else if (chunck.w_side == BOT_A)
			i[0] = stack->stack_a->tail->r_pos;
		else if (chunck.w_side == TOP_B)
			i[0] = stack->stack_b->head->r_pos;
		else if (chunck.w_side == BOT_B)
			i[0] = stack->stack_b->tail->r_pos;
		if (i[0] > others.side[AVERAGE].num_final)
			i[1] = HIGHERS;	
		else if (i[0] < others.side[AVERAGE].num_init)
			i[1] = LOWERS;	
		else
			i[1] = AVERAGE;			
		calculate_move(stack, chunck.w_side, others.side[i[1]].w_side);
	}
	return(others);
}

void	calculate_move(t_core *core, t_side from, t_side to)
{
	if (from == TOP_A && to == BOT_A)
		control_moves(RA, core);
	else if (from == TOP_A && (to == TOP_B  || to == BOT_B) )
		control_moves(PB, core);
	if (from == TOP_A && to == BOT_B)
		control_moves(RB, core);
	if (from == BOT_A)
		control_moves(RRA, core);
	if (from == BOT_A && (to == TOP_B  || to == BOT_B) )
		control_moves(PB, core);
	if (from == BOT_A && to == BOT_B)
		control_moves(RB, core);
	if (from == TOP_B && to == BOT_B)
		control_moves(RB, core);
	else if (from == TOP_B && (to == TOP_A  || to == BOT_A) )
		control_moves(PA, core);
	if (from == TOP_B && to == BOT_A)
		control_moves(RA, core);
	if (from == BOT_B)
		control_moves(RRB, core);
	if (from == BOT_B && (to == TOP_A  || to == BOT_A) )
		control_moves(PA, core);
	if (from == BOT_B && to == BOT_A)
		control_moves(RA, core);
}

t_divides	aux_create_chuncks(t_divides chunck, t_chunck w_chunk)
{
	if (w_chunk == LOWERS)
	{
		chunck.mod = chunck.size % 3;
		chunck.size /= 3;
		chunck.w_side = BOT_B;
		chunck.num_final = chunck.num_init + chunck.size - 1;
	}
	else
	{
		chunck.w_side = chunck.w_side - 1;
		chunck.num_init = chunck.num_final + 1;
		chunck.num_final = chunck.num_init + chunck.size - 1;
	}
	chunck.w_chunck = w_chunk;
	chunck = resolve_mod(chunck);
	return (chunck);
}

t_divides	resolve_mod(t_divides chunck)
{
	if (chunck.mod > 0 && chunck.w_chunck == LOWERS)
		chunck.size++;
	if (chunck.mod > 0 && chunck.w_chunck == LOWERS)
		chunck.num_final++;
	if (chunck.mod == 1 && chunck.w_chunck == AVERAGE)
		chunck.size--;
	if (chunck.mod == 1 && chunck.w_chunck == AVERAGE)
		chunck.num_final--;
	if (chunck.mod == 2 && chunck.w_chunck == HIGHERS)
		chunck.size--;
	if (chunck.mod == 2 && chunck.w_chunck == HIGHERS)
		chunck.num_final--;
	return(chunck);
}

void			control_moves(t_moves new_move, t_core *core)
{
	t_moves att_move;

	att_move = NONE;
	if (new_move != NONE)
		core->func[new_move]();
	if ((new_move == SA && core->last_move == SB) || (new_move == SB &&
		core->last_move == SA))
		att_move = SS;
	else if ((new_move == RA && core->last_move == RB) || (new_move == RB &&
		core->last_move == RA))
		att_move = RR;
	else if ((new_move == RRA && core->last_move == RRB) || (new_move == RRB &&
		core->last_move == RRA))
		att_move = RRR;
	if (att_move == NONE)
		print_moves(core);
	else
		new_move = att_move;
	core->last_move = new_move;
}

void	print_moves(t_core *core)
{
	if (core->last_move == SA)
		ft_printf("sa\n");
	else if (core->last_move == SB)
		ft_printf("sb\n");
	else if (core->last_move == SS)
		ft_printf("ss\n");
	else if (core->last_move == PA)
		ft_printf("pa\n");
	else if (core->last_move == PB)
		ft_printf("pb\n");
	else if (core->last_move == RA)
		ft_printf("ra\n");
	else if (core->last_move == RB)
		ft_printf("rb\n");
	else if (core->last_move == RR)
		ft_printf("rr\n");
	else if (core->last_move == RRA)
		ft_printf("rra\n");
	else if (core->last_move == RRB)
		ft_printf("rrb\n");
	else if (core->last_move == RRR)
		ft_printf("rrr\n");
}

t_core	*core_utils(void)
{
	static t_core	*stacks = NULL;

	if (!stacks)
	{
		stacks = ft_gc_calloc_root(1, sizeof(t_core), GC_DATA, "history");
		stacks->stack_a = ((t_gc_list *)ft_gc_content_root("stack_a")->content)->content;
		stacks->stack_b = ft_gc_calloc_root(1, sizeof(t_meta_ilist), GC_DATA,
				"stack_b");
		stacks->stack_b->w_side = TOP_B;
		stacks->stack_b->w_chunck = ALL;
		stacks->last_move = NONE;
		stacks->func[0] = &sa;
		stacks->func[1] = &sb;
		stacks->func[2] = &ss;
		stacks->func[3] = &pa;
		stacks->func[4] = &pb;
		stacks->func[5] = &ra;
		stacks->func[6] = &rb;
		stacks->func[7] = &rr;
		stacks->func[8] = &rra;
		stacks->func[9] = &rrb;
		stacks->func[10] = &rrr;
	}
	return (stacks);
}

int	check_order(t_meta_ilist *nums)
{
	t_ilist	*aux;

	if (!nums)
		return (1);
	aux = nums->head;
	while (aux->next)
	{
		if (aux->num > aux->next->num)
			return (1);
		aux = aux->next;
	}
	return (0);
}
