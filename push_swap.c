/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgomes-d <rgomes-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 18:39:09 by rgomes-d          #+#    #+#             */
/*   Updated: 2025/09/30 11:10:11 by rgomes-d         ###   ########.fr       */
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
	nums = parsing_args(argv, argc);
	if (!nums || init_sorting(nums))
		return (handle_error());
	control_moves(NONE, core_utils());
	ft_gc_end();
	return (0);
}

int	init_sorting(t_meta_ilist *stack_a)
{
	t_divides	main;
	t_ilist		*aux;
	t_core		*stack;

	if (!stack_a || stack_a->size == 0)
		return (1);
	aux = stack_a->head;
	while (aux->next)
	{
		if (aux->num > aux->next->num)
			break ;
		aux = aux->next;
	}
	stack = core_utils();
	if (!aux->next || !stack)
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
