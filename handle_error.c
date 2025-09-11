/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgomes-d <rgomes-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 19:27:24 by rgomes-d          #+#    #+#             */
/*   Updated: 2025/09/11 20:22:19 by rgomes-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	handle_error(t_error error)
{
	if (error == INVALID_ARGS)
		ft_putstr_fd("Error\nhas not arguments\n",2);
	if (error == INVALID_NUMBER)
		ft_putstr_fd("Error\nnumber invalid\n",2);
	if (error == NOT_INT_ERROR)
		ft_putstr_fd("Error\nany argument has not number\n",2);
	ft_gc_end();
	return (1);
}
