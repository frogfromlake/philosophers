/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   times.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fquist <fquist@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/10 18:27:38 by fquist            #+#    #+#             */
/*   Updated: 2022/05/15 17:24:14 by fquist           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/philo.h"

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

void	sleep_ms(t_philo *philo, time_t val)
{
	time_t	time;

	time = get_time();
	while (1)
	{
		if (time + val < get_time())
			break ;
		time_to_die(philo);
		usleep(800);
	}
}

void	time_to_die(t_philo *philo)
{
	pthread_mutex_lock(&data()->init_lock);
	if (get_time() - philo->last_meal > data()->input.ttd)
	{
		if (philo->dead == false)
		{
			philo->dead = true;
			data()->init_routine = false;
			print_msg(philo->id, "is dead.");
			data()->printable = false;
		}
	}
	pthread_mutex_unlock(&data()->init_lock);
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
