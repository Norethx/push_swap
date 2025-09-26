/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moves.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgomes-d <rgomes-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 14:53:41 by rgomes-d          #+#    #+#             */
/*   Updated: 2025/09/26 14:32:53 by rgomes-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	sa(void)
{
	t_core	*core;

	core = core_utils();
	if (swap(&core->stack_a))
		return (1);
	return (0);
}
int	sb(void)
{
	t_core	*core;

	core = core_utils();
	if (swap(&core->stack_b))
		return (1);
	return (0);
}

int	ss(void)
{
	t_core	*core;

	core = core_utils();
	if (swap(&core->stack_a) && swap(&core->stack_b))
		return (1);
	return (0);
}

int	pa(void)
{
	t_core	*core;

	core = core_utils();
	if (push(&core->stack_a, &core->stack_b))
		return (1);
	return (0);
}
int	pb(void)
{
	t_core	*core;

	core = core_utils();
	if (push(&core->stack_b, &core->stack_a))
		return (1);
	return (0);
}
