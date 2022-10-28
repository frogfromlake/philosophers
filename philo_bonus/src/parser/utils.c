/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fquist <fquist@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/09 22:29:10 by fquist            #+#    #+#             */
/*   Updated: 2022/05/15 15:49:03 by fquist           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/philo_bonus.h"

static int	is_sign(char c)
{
	if (c == '+' || c == '-')
		return (true);
	return (false);
}

static int	is_space(int c)
{
	if (c == ' ' || c == '\t' || c == '\n'
		|| c == '\v' || c == '\f' || c == '\r')
		return (true);
	return (false);
}

static int	is_digit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	else
		return (0);
}

int	philo_atoi(const char *str)
{
	long long int	n;
	int				is_negative;

	n = 0;
	is_negative = 1;
	while (is_space(*str))
		str++;
	if (is_sign(*str))
	{
		if (*str == '-')
			is_negative = -1;
		str++;
	}
	while (is_digit(*str))
	{
		n = (n * 10) + (*str - '0');
		if (n < 0 && is_negative == -1)
			return (0);
		else if (n < 0 && is_negative == 1)
			return (-1);
		str++;
	}
	if (n > INT_MAX || n < INT_MIN)
		return (INT_MAX);
	return (n * is_negative);
}

void	free_array(char **array)
{
	int	i;

	i = 0;
	while (array[i])
	{
		free(array[i]);
		array[i] = NULL;
		i++;
	}
	free(array);
	array = NULL;
}
