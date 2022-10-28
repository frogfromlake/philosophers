/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fquist <fquist@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/10 18:28:30 by fquist            #+#    #+#             */
/*   Updated: 2022/05/15 17:24:31 by fquist           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/philo.h"

static bool	check_conditions(t_philo *philo)
{
	pthread_mutex_lock(&data()->eaten);
	if (data()->input.to_eat > -1 && philo->meals == data()->input.to_eat)
	{
		pthread_mutex_unlock(&data()->eaten);
		return (true);
	}
	if (philo->dead == true)
	{
		pthread_mutex_unlock(&data()->eaten);
		return (true);
	}
	pthread_mutex_unlock(&data()->eaten);
	return (false);
}

static void	philo_status(int status, t_philo *philo)
{
	if (status == sleeping)
	{
		pthread_mutex_lock(&data()->init_lock);
		print_msg(philo->id, "is sleeping.");
		pthread_mutex_unlock(&data()->init_lock);
		philo->status = thinking;
		sleep_ms(philo, data()->input.tts);
	}
	else if (status == thinking)
	{
		pthread_mutex_lock(&data()->init_lock);
		print_msg(philo->id, "is thinking.");
		pthread_mutex_unlock(&data()->init_lock);
		philo->status = waiting;
	}
	else if (status == lonely)
	{
		take_one_fork(philo, philo);
		pthread_mutex_lock(&data()->init_lock);
		print_msg(philo->id, "has taken a fork.");
		pthread_mutex_unlock(&data()->init_lock);
		sleep_ms(philo, data()->input.ttd);
		philo->dead = true;
	}
}

bool	init_routine(void)
{
	pthread_mutex_lock(&data()->init_lock);
	if (data()->init_routine == true)
	{
		pthread_mutex_unlock(&data()->init_lock);
		return (true);
	}
	pthread_mutex_unlock(&data()->init_lock);
	return (false);
}

void	*routine(void *varg)
{
	t_philo	*philo;

	philo = (t_philo *)varg;
	while (!init_routine())
		usleep(10);
	philo->last_meal = get_time();
	if (philo->id % 2)
		sleep_ms(philo, data()->input.tte - 1);
	while (init_routine())
	{
		if (philo->status == lonely)
			philo_status(lonely, philo);
		if (philo->status == sleeping)
			philo_status(sleeping, philo);
		if (philo->status == thinking)
			philo_status(thinking, philo);
		if (philo->status == waiting)
			eating(philo);
		if (check_conditions(philo) == 1)
			break ;
	}
	return (NULL);
}
