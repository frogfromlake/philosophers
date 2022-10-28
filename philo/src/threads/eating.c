/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eating.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fquist <fquist@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/24 14:17:57 by fquist            #+#    #+#             */
/*   Updated: 2022/05/15 17:10:21 by fquist           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/philo.h"

void	take_one_fork(t_philo *philo, t_philo *check)
{
	bool	own_fork;

	own_fork = false;
	while (own_fork == false)
	{
		pthread_mutex_lock(&philo->lock_fork);
		if (philo->fork)
		{
			philo->fork = false;
			own_fork = true;
		}
		pthread_mutex_unlock(&philo->lock_fork);
		time_to_die(check);
		usleep(50);
	}
}

void	take_forks(t_philo *philo, int id)
{
	take_one_fork(philo, philo);
	pthread_mutex_lock(&data()->init_lock);
	print_msg(id, "has taken a fork.");
	pthread_mutex_unlock(&data()->init_lock);
	if (!data()->philos[id])
		take_one_fork(data()->philos[0], philo);
	else
		take_one_fork(data()->philos[id], philo);
	pthread_mutex_lock(&data()->init_lock);
	print_msg(id, "has taken another fork.");
	pthread_mutex_unlock(&data()->init_lock);
}

void	return_forks(t_philo *philo, int neighbour)
{
	pthread_mutex_lock(&philo->lock_fork);
	philo->fork = true;
	pthread_mutex_unlock(&philo->lock_fork);
	pthread_mutex_lock(&data()->philos[neighbour]->lock_fork);
	data()->philos[neighbour]->fork = true;
	pthread_mutex_unlock(&data()->philos[neighbour]->lock_fork);
}

void	eating(t_philo *philo)
{
	take_forks(philo, philo->id);
	philo->meals++;
	philo->last_meal = get_time();
	pthread_mutex_lock(&data()->init_lock);
	print_msg(philo->id, "is eating.");
	pthread_mutex_unlock(&data()->init_lock);
	sleep_ms(philo, data()->input.tte);
	philo->status = sleeping;
	if (!data()->philos[philo->id])
		return_forks(philo, 0);
	else
		return_forks(philo, philo->id);
}
