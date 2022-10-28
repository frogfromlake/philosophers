/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eating.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fquist <fquist@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/24 14:17:57 by fquist            #+#    #+#             */
/*   Updated: 2022/05/14 23:36:20 by fquist           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/philo_bonus.h"

static void	take_forks(int id, t_data *data)
{
	sem_wait(data->lock_fork);
	print_msg(id, "has taken a fork.", data);
	sem_wait(data->lock_fork);
	print_msg(id, "has taken another fork.", data);
}

void	eating(t_philo *philo, t_data *data)
{
	take_forks(philo->id, data);
	sem_wait(data->eaten);
	philo->meals++;
	philo->last_meal = get_time();
	sem_post(data->eaten);
	sem_wait(data->init_lock);
	print_msg(philo->id, "is eating.", data);
	sem_post(data->init_lock);
	if (check_meals(philo))
		sem_post(data->total_meals);
	sleep_ms(data->input.tte);
	sem_post(data->lock_fork);
	sem_post(data->lock_fork);
	philo->status = thinking;
}
