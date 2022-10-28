/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   times_and_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fquist <fquist@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/10 18:27:38 by fquist            #+#    #+#             */
/*   Updated: 2022/05/15 15:40:09 by fquist           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/philo_bonus.h"

time_t	get_time(void)
{
	struct timeval	tp;
	long			ms;
	static long		start;

	gettimeofday(&tp, NULL);
	ms = tp.tv_sec * 1000;
	ms += tp.tv_usec / 1000;
	if (start == 0)
		start = ms;
	return (ms - start);
}

void	sleep_ms(time_t val)
{
	time_t	time;

	time = get_time();
	while (1)
	{
		if (time + val < get_time())
			break ;
		usleep(700);
	}
}

int	str_cmp(const char *s1, const char *s2)
{
	size_t			i;
	unsigned char	*new1;
	unsigned char	*new2;

	i = 0;
	new1 = (unsigned char *)s1;
	new2 = (unsigned char *)s2;
	while (new1[i] && new2[i] && (new1[i] - new2[i] == 0))
		i++;
	if (!new1[i] && new2[i])
		return (-1);
	else if (new1[i] && !new2[i])
		return (1);
	else if (!new1[i] && !new2[i])
		return (0);
	else
		return (new1[i] - new2[i]);
}
