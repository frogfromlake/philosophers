/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fquist <fquist@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 22:30:58 by dmontema          #+#    #+#             */
/*   Updated: 2022/05/15 16:54:01 by fquist           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/philo.h"

t_philo	*new_philo(int i)
{
	t_philo	*philo;

	philo = malloc(sizeof(t_philo));
	if (!philo)
		error_msg("Error: philo couldn't be allocated.", i);
	philo->dead = false;
	philo->id = i + 1;
	philo->status = waiting;
	philo->meals = 0;
	philo->fork = true;
	philo->last_meal = 0;
	philo->t_meals = 0;
	if (pthread_mutex_init(&philo->lock_fork, NULL) != 0)
		error_msg("Error: couldn't create mutex.", i);
	if ((pthread_create(&philo->th_id, NULL, &routine, philo)) == 0)
		data()->th_nbr++;
	else
		error_msg("Error: couldn't create thread.", i);
	return (philo);
}

void	init_philos(void)
{
	int	i;

	data()->philos = malloc(sizeof(t_philo *) * data()->input.p_nbr + 1);
	i = -1;
	if (!data()->philos)
		error_msg("Error: philos couldn't be allocated.", i);
	if (pthread_mutex_init(&data()->print, NULL) != 0)
		error_msg("Error: couldn't create Mutex.", i);
	if (pthread_mutex_init(&data()->init_lock, NULL) != 0)
		error_msg("Error: couldn't create Mutex.", i);
	if (pthread_mutex_init(&data()->eaten, NULL) != 0)
		error_msg("Error: couldn't create Mutex.", i);
	while (++i < data()->input.p_nbr)
		data()->philos[i] = new_philo(i);
	if (data()->th_nbr == 1)
		data()->philos[0]->status = lonely;
	pthread_mutex_lock(&data()->init_lock);
	data()->philos[i] = NULL;
	data()->init_routine = true;
	get_time();
	pthread_mutex_unlock(&data()->init_lock);
	join_threads();
	return ;
}

void	init_data(char **argv)
{
	data()->input.p_nbr = philo_atoi(argv[1]);
	data()->input.ttd = philo_atoi(argv[2]);
	data()->input.tte = philo_atoi(argv[3]);
	data()->input.tts = philo_atoi(argv[4]);
	if (argv[5])
		data()->input.to_eat = philo_atoi(argv[5]);
	else if (!argv[5])
		data()->input.to_eat = -1;
	data()->th_nbr = 0;
	data()->printable = true;
	data()->init_routine = false;
	init_philos();
	return ;
}
