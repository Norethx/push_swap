/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgomes-d <rgomes-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 18:39:09 by rgomes-d          #+#    #+#             */
/*   Updated: 2025/09/11 20:08:41 by rgomes-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static char	**duplicate_argv(char **argv);
static int	ft_verify_numbers(char **nums);

int	main(int argc, char **argv)
{
	char	**nums;

	if (argc <= 1)
		return (handle_error(INVALID_ARGS));
	if (ft_gc_init())
		return (handle_error(INVALID_ARGS));
	if (argc == 2)
		nums = ft_gcfct_arr_register((void **)ft_split(argv[1], ' '),
				GC_DATA)->content;
	else
		nums = duplicate_argv(argv);
	if (ft_verify_numbers(nums))
		return (handle_error(NOT_INT_ERROR));

	ft_gc_end();
	return (0);
}

static int	ft_verify_numbers(char **nums)
{
	int	i[2];

	i[0] = 0;
	if (!nums[0])
		return (1);
	while (nums[i[0]])
	{
		i[1] = 0;
		while (ft_isspace(nums[i[0]][i[1]]))
			i[1]++;
		if (nums[i[0]][i[1]] == '-' || nums[i[0]][i[1]] == '+')
			i[1]++;
		while (nums[i[0]][i[1]])
		{
			if (!ft_strchr("0123456789", nums[i[0]][i[1]]))
				return (1);
			i[1]++;
		}
		i[0]++;
	}
	return (0);
}

static char	**duplicate_argv(char **argv)
{
	char	**nums;
	int		size_arr;
	int		i;

	i = 0;
	size_arr = ft_size_chrarr(argv);
	nums = ft_gc_calloc(size_arr, sizeof(char *), GC_DATA)->content;
	if (!nums)
		return (NULL);
	while (i < size_arr - 1 || argv[i + 1])
	{
		nums[i] = argv[i + 1];
		i++;
	}
	nums[i] = NULL;
	return (nums);
}
