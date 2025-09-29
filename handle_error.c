/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgomes-d <rgomes-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 19:27:24 by rgomes-d          #+#    #+#             */
/*   Updated: 2025/09/29 11:50:43 by rgomes-d         ###   ########.fr       */
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
