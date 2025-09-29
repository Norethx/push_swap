/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgomes-d <rgomes-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 18:39:09 by rgomes-d          #+#    #+#             */
/*   Updated: 2025/09/29 14:00:17 by rgomes-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	main(int argc, char **argv)
{
	t_meta_ilist	*nums;

	if (argc <= 1)
		return (0);
	if (ft_gc_init())
		return (handle_error());
	nums = parsing_args(argv);
	if (!nums || init_sorting(nums))
		return (1);
	control_moves(NONE, core_utils());
	ft_gc_end();
	return (0);
}

int	init_sorting(t_meta_ilist *stack_a)
{
	t_divides	main;
	t_ilist		*aux;
	t_core		*stack;

	if (!stack_a)
		return (1);
	aux = stack_a->head;
	while (aux->next)
	{
		if (aux->num > aux->next->num)
			break ;
		aux = aux->next;
	}
	stack = core_utils();
	if (!aux->num || !stack)
		return (1);
	main.num_final = stack->stack_a->size;
	main.num_init = 1;
	main.size = stack->stack_a->size;
	main.w_chunk = ALL;
	main.w_side = TOP_A;
	main.mod = 0;
	sorting(main, stack);
	return (0);
}

t_core	*core_utils(void)
{
	static t_core	*stacks = NULL;

	if (!stacks)
	{
		stacks = ft_gc_calloc_root(1, sizeof(t_core), GC_DATA, "history");
		stacks->stack_a = ft_gc_content_root("stack_a")->content;
		stacks->stack_a = ((t_gc_list *)stacks->stack_a)->content;
		stacks->stack_b = ft_gc_calloc_root(1, sizeof(t_meta_ilist), GC_DATA,
				"stack_b");
		stacks->stack_b->w_side = TOP_B;
		stacks->stack_b->w_chunk = ALL;
		stacks->last_move = NONE;
	}
	return (stacks);
}
