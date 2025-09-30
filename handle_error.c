/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgomes-d <rgomes-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 19:27:24 by rgomes-d          #+#    #+#             */
/*   Updated: 2025/09/29 20:52:26 by rgomes-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	handle_error(void)
{
	ft_putstr_fd("Error\n", 2);
	ft_gc_end();
	return (1);
}

int	verify_dup(t_meta_ilist **rtn)
{
	t_ilist	*aux[2];

	aux[0] = rtn[0]->head;
	while (aux[0])
	{
		aux[1] = rtn[0]->head;
		while (aux[1])
		{
			if (aux[0] != aux[1] && aux[0]->num == aux[1]->num)
				return (1);
			if (aux[0] != aux[1] && aux[0]->num > aux[1]->num)
				aux[0]->r_pos++;
			aux[1] = aux[1]->next;
		}
		aux[0]->r_pos++;
		aux[0] = aux[0]->next;
	}
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
