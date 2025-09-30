/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aux_moves.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgomes-d <rgomes-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/29 13:57:07 by rgomes-d          #+#    #+#             */
/*   Updated: 2025/09/29 17:44:55 by rgomes-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	calculate_move(t_core *core, t_side from, t_divides chunk)
{
	if (from == TOP_A && chunk.w_side == BOT_A)
		control_moves(RA, core);
	else if (from == TOP_A && (chunk.w_side > 1))
		control_moves(PB, core);
	if (from == TOP_A && chunk.w_side == BOT_B)
		control_moves(RB, core);
	if (from == BOT_A)
		control_moves(RRA, core);
	if (from == BOT_A && (chunk.w_side > 1))
		control_moves(PB, core);
	if (from == BOT_A && chunk.w_side == BOT_B)
		control_moves(RB, core);
	if (from == TOP_B && chunk.w_side == BOT_B)
		control_moves(RB, core);
	else if (from == TOP_B && (chunk.w_side < 2))
		control_moves(PA, core);
	if (from == TOP_B && chunk.w_side == BOT_A)
		control_moves(RA, core);
	if (from == BOT_B)
		control_moves(RRB, core);
	if (from == BOT_B && (chunk.w_side < 2))
		control_moves(PA, core);
	if (from == BOT_B && chunk.w_side == BOT_A)
		control_moves(RA, core);
	last_sort(core, chunk);
}

void	control_moves(t_moves new_move, t_core *core)
{
	t_moves	att_move;

	att_move = new_move;
	handle_moves(new_move);
	if ((new_move == SA && core->last_move == SB) || (new_move == SB
			&& core->last_move == SA))
		att_move = SS;
	else if ((new_move == RA && core->last_move == RB) || (new_move == RB
			&& core->last_move == RA))
		att_move = RR;
	else if ((new_move == RRA && core->last_move == RRB) || (new_move == RRB
			&& core->last_move == RRA))
		att_move = RRR;
	if ((new_move == RRA && core->last_move == RA) || (new_move == RA
			&& core->last_move == RRA) || (new_move == RRB
			&& core->last_move == RB) || (new_move == RB
			&& core->last_move == RRB))
	{
		att_move = NONE;
		core->last_move = NONE;
	}
	if (att_move == new_move)
		print_moves(core);
	new_move = att_move;
	core->last_move = new_move;
}

void	sort_three(t_meta_ilist *a)
{
	int	x[3];

	x[0] = a->head->r_pos;
	x[1] = a->head->next->r_pos;
	x[2] = a->tail->r_pos;
	if (x[0] > x[1] && x[1] < x[2] && x[0] < x[2])
		control_moves(SA, core_utils());
	else if (x[0] > x[1] && x[1] > x[2])
	{
		control_moves(SA, core_utils());
		control_moves(RRA, core_utils());
	}
	else if (x[0] > x[1] && x[1] < x[2] && x[0] > x[2])
		control_moves(RA, core_utils());
	else if (x[0] < x[1] && x[1] > x[2] && x[0] < x[2])
	{
		control_moves(SA, core_utils());
		control_moves(RA, core_utils());
	}
	else if (x[0] < x[1] && x[1] > x[2] && x[0] > x[2])
		control_moves(RRA, core_utils());
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
