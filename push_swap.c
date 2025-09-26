/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgomes-d <rgomes-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 18:39:09 by rgomes-d          #+#    #+#             */
/*   Updated: 2025/09/25 21:12:50 by rgomes-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int				check_order(t_meta_ilist *nums);
void			control_moves(t_moves new_move);
void			init_sorting(t_core *stack);
int				sorting(t_divides chunck, t_core *stack);
t_all_chunks	create_chuncks(t_divides chunck, t_core *stack);
t_divides		aux_create_chuncks(t_divides chunck, t_chunck w_chunk);

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
	main.w_side = A;
	main.mod = 0;
	sorting(main, stack);
}

int	sorting(t_divides chunck, t_core *stack)
{
	t_all_chunks	others;

	if (chunck.size <= 2)
		return (0);
	others = create_chuncks(chunck, stack);
	// sorting(others.HIGHERS, stack);
	// sorting(others.AVERAGE, stack);
	// sorting(others.LOWERS, stack);
	return (0);
}

t_all_chunks	create_chuncks(t_divides chunck, t_core *stack)
{
	t_all_chunks	others;
	t_ilist			*ref;
	int				i;

	others.LOWERS = aux_create_chuncks(chunck, LOWERS);
	others.AVERAGE = aux_create_chuncks(others.LOWERS, AVERAGE);
	others.HIGHERS = aux_create_chuncks(others.AVERAGE, HIGHERS);
	ref = stack->stack_a->tail;
	while (stack->stack_a->head != ref)
	{
		i = stack->stack_a->head->r_pos;
		if (i >= others.LOWERS.num_init && i <= others.LOWERS.num_final)
		{
			control_moves(PB);
			control_moves(RB);
		}
		else if (i >= others.AVERAGE.num_init && i <= others.AVERAGE.num_final)
			control_moves(PB);
		else if (i >= others.HIGHERS.num_init && i <= others.HIGHERS.num_final)
			control_moves(RA);
	}
	i = stack->stack_a->head->r_pos;
	if (i >= others.LOWERS.num_init && i <= others.LOWERS.num_final)
	{
		control_moves(PB);
		control_moves(RB);
	}
	else if (i >= others.AVERAGE.num_init && i <= others.AVERAGE.num_final)
		control_moves(PB);
	else if (i >= others.HIGHERS.num_init && i <= others.HIGHERS.num_final)
		control_moves(RA);
	return (others);
}

t_divides	aux_create_chuncks(t_divides chunck, t_chunck w_chunk)
{
	if (w_chunk == LOWERS)
	{
		chunck.size /= 3;
		chunck.mod %= 3;
		chunck.w_side = A;
		chunck.num_final = chunck.num_init + chunck.size - 1;
		if (chunck.mod > 0)
			chunck.size++;
		if (chunck.mod > 0)
			chunck.num_final++;
	}
	else
	{
		if (chunck.mod == 1 && w_chunk == AVERAGE)
			chunck.size--;
		if (chunck.mod == 1 && w_chunk == AVERAGE)
			chunck.num_final--;
		if (chunck.mod == 2 && w_chunk == HIGHERS)
			chunck.size--;
		if (chunck.mod == 2 && w_chunk == HIGHERS)
			chunck.num_final--;
		chunck.w_side = B;
		chunck.num_init = chunck.num_final + 1;
		chunck.num_final = chunck.num_init + chunck.size - 1;
	}
	chunck.w_chunck = w_chunk;
	return (chunck);
}

void	control_moves(t_moves new_move)
{
	t_core	*core;
	int		(*func[11])(void);

	func[0] = &sa;
	func[1] = &sb;
	func[2] = &ss;
	func[3] = &pa;
	func[4] = &pb;
	func[5] = &ra;
	func[6] = &rb;
	func[7] = &rr;
	func[8] = &rra;
	func[9] = &rrb;
	func[10] = &rrr;
	core = core_utils();
	func[new_move]();
	core->last_move = new_move;
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
		stacks->stack_b->w_side = B;
		stacks->stack_b->w_chunck = ALL;
		stacks->last_move = NONE;
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
