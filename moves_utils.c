/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moves_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgomes-d <rgomes-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 14:53:45 by rgomes-d          #+#    #+#             */
/*   Updated: 2025/09/27 13:30:50 by rgomes-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h".

int	ra(void)
{
	t_core	*core;

	core = core_utils();
	rotate(&core->stack_a);
	return (1);
}
int	rb(void)
{
	t_core	*core;

	core = core_utils();
	rotate(&core->stack_b);
	return (1);
}

int	rr(void)
{
	t_core	*core;

	core = core_utils();
	rotate(&core->stack_a);
	rotate(&core->stack_b);
	return (1);
}

int	rra(void)
{
	t_core	*core;

	core = core_utils();
	reverse_rotate(&core->stack_a);
	return (1);
}
int	rrb(void)
{
	t_core	*core;

	core = core_utils();
	reverse_rotate(&core->stack_b);
	return (1);
}
