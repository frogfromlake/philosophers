/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fquist <fquist@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/10 18:28:30 by fquist            #+#    #+#             */
/*   Updated: 2022/05/15 16:12:40 by fquist           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/philo_bonus.h"

static void	philo_status(int status, t_philo *philo, t_data *data)
{
	if (status == thinking)
	{
		sem_wait(data->init_lock);
		print_msg(philo->id, "is thinking.", data);
		sem_post(data->init_lock);
		philo->status = sleeping;
	}
	else if (status == sleeping)
	{
		sem_wait(data->init_lock);
		print_msg(philo->id, "is sleeping.", data);
		sem_post(data->init_lock);
		sleep_ms(data->input.tts);
		philo->status = waiting;
	}
	else if (status == lonely)
	{
		sem_wait(data->init_lock);
		print_msg(philo->id, "has taken a fork.", data);
		sem_post(data->init_lock);
		sleep_ms(data->input.ttd);
	}
}

void	routine(t_philo *philo, t_data *data)
{
	if (philo->id % 2)
		sleep_ms(data->input.tte - 1);
	while (1)
	{
		if (philo->status == lonely)
			philo_status(lonely, philo, data);
		sem_wait(data->eaten);
		if (data->input.to_eat > -1 && philo->meals == data->input.to_eat)
			philo->meals++;
		sem_post(data->eaten);
		if (philo->status == waiting)
			eating(philo, data);
		if (philo->status == thinking)
			philo_status(thinking, philo, data);
		if (philo->status == sleeping)
			philo_status(sleeping, philo, data);
	}
	return ;
}
