/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reaper_thread.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fquist <fquist@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/01 18:51:16 by fquist            #+#    #+#             */
/*   Updated: 2022/05/15 16:13:35 by fquist           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/philo_bonus.h"

bool	check_meals(t_philo *philo)
{
	sem_wait(data()->eaten);
	if (philo->meals == data()->input.to_eat)
	{
		sem_post(data()->eaten);
		return (true);
	}
	sem_post(data()->eaten);
	return (false);
}

static void	*reaper_duty(void *arg)
{
	t_philo	*philo;
	int		total_meals;

	total_meals = 0;
	philo = (t_philo *)arg;
	while (1)
	{
		if ((get_time() - philo->last_meal) > data()->input.ttd)
		{
			if (data()->input.to_eat > -1)
				sem_post(data()->total_meals);
			sem_wait(data()->print);
			data()->init_routine = false;
			printf("%ld	%d%s\n", get_time(), philo->id,
				" is dead.");
			exit(EXIT_SUCCESS);
		}
		usleep(100);
	}
	return (NULL);
}

int	reaper_awake(t_philo *philo, int i)
{
	pthread_t	reaper;

	(void)i;
	if (pthread_create(&reaper, NULL, &reaper_duty, philo) != 0)
		return (1);
	pthread_detach(reaper);
	return (0);
}
