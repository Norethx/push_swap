/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_args.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgomes-d <rgomes-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/24 11:34:34 by rgomes-d          #+#    #+#             */
/*   Updated: 2025/09/27 13:36:33 by rgomes-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static char		**duplicate_argv(char **argv);
static int		ft_verify_numbers(char **nums);
static char		**split_args(char **argv);
static int		convert_number(t_meta_ilist **rtn, char **nums);
static int		verify_dup(t_meta_ilist **rtn);

t_meta_ilist	*parsing_args(char **args)
{
	char			**nums;
	t_meta_ilist	*rtn;

	nums = duplicate_argv(args);
	if (ft_verify_numbers(nums))
	{
		handle_error();
		return (NULL);
	}
	rtn = ft_gc_calloc_root(1, sizeof(t_meta_ilist), GC_DATA, "stack_a");
	rtn->size = ft_size_chrarr(nums);
	rtn->w_chunk = ALL;
	rtn->w_side = TOP_A;
	if (convert_number(&rtn, nums) || verify_dup(&rtn))
	{
		handle_error();
		return (NULL);
	}
	return (rtn);
}

static int	verify_dup(t_meta_ilist **rtn)
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

static int	convert_number(t_meta_ilist **rtn, char **nums)
{
	t_ilist	*aux[2];
	int		i;

	i = 0;
	aux[0] = NULL;
	while (nums[i])
	{
		aux[1] = aux[0];
		aux[0] = ft_gc_calloc_root(1, sizeof(t_ilist), GC_DATA, "core");
		aux[0]->num = ft_atoi(nums[i]);
		if (aux[0]->num == 0 && nums[i][ft_strlen(nums[i]) - 1] != '0')
			return (1);
		aux[0]->prev = aux[1];
		if (!aux[1])
			rtn[0]->head = aux[0];
		else
			aux[1]->next = aux[0];
		i++;
	}
	rtn[0]->tail = aux[0];
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
	i = 0;
	return (split_args(nums));
}

static char	**split_args(char **argv)
{
	int		size;
	int		i;
	char	*aux;
	char	**rtn;

	size = ft_size_chrarr(argv) + ft_arraylen_chr(argv);
	aux = ft_gc_calloc_root(1, size + 1, GC_DATA, "aux");
	i = 0;
	if (!aux)
		return (NULL);
	while (argv[i])
	{
		ft_strlcat(aux, argv[i++], size);
		if (argv[i])
			ft_strlcat(aux, " ", size);
	}
	rtn = ft_gcfct_arr_register_root((void **)ft_split(aux, ' '), GC_DATA,
			"args");
	if (!rtn)
		return (NULL);
	ft_gc_del_root("aux");
	ft_gc_collect();
	return (rtn);
}
