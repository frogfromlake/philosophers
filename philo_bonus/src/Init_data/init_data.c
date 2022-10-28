/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fquist <fquist@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 22:30:58 by dmontema          #+#    #+#             */
/*   Updated: 2022/05/15 16:11:48 by fquist           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/philo_bonus.h"

static t_philo	*new_philo(int i)
{
	t_philo		*philo;

	philo = malloc(sizeof(t_philo));
	if (!philo)
		error_msg("couldn't allocate philo.", -2);
	data()->pid[i] = fork();
	if (data()->pid[i] == 0)
	{
		philo->id = i + 1;
		philo->status = waiting;
		if (data()->input.p_nbr == 1)
			philo->status = lonely;
		philo->meals = 0;
		philo->fork = true;
		philo->last_meal = 0;
		reaper_awake(philo, philo->id);
		routine(philo, data());
	}
	return (philo);
}

static void	prepare_semaphores(void)
{
	t_data	*dat;

	dat = data();
	sem_unlink(TOTAL_MEALS);
	sem_unlink(LOCK_FORK);
	sem_unlink(PRINT);
	sem_unlink(INIT_LOCK);
	sem_unlink(EATEN);
	sem_unlink(STATUS_LOCK);
	dat->total_meals = sem_open(TOTAL_MEALS, O_CREAT | O_EXCL, 0644, 0);
	dat->lock_fork = sem_open(LOCK_FORK, O_CREAT | O_EXCL,
			0644, data()->input.p_nbr);
	dat->print = sem_open(PRINT, O_CREAT | O_EXCL, 0644, 1);
	dat->init_lock = sem_open(INIT_LOCK, O_CREAT | O_EXCL, 0644, 1);
	dat->eaten = sem_open(EATEN, O_CREAT | O_EXCL, 0644, 1);
	dat->status_lock = sem_open(STATUS_LOCK, O_CREAT | O_EXCL, 0644, 1);
	if (!data()->total_meals || !data()->lock_fork || !data()->init_lock
		|| !data()->eaten || !data()->status_lock)
		error_msg("couldn't create Semaphore", -1);
	sem_unlink(TOTAL_MEALS);
	sem_unlink(LOCK_FORK);
	sem_unlink(PRINT);
	sem_unlink(INIT_LOCK);
	sem_unlink(EATEN);
	sem_unlink(STATUS_LOCK);
}

static void	init_philos(void)
{
	data()->philos = malloc(sizeof(t_philo *) * data()->input.p_nbr);
	if (!data()->philos)
		error_msg("philos couldn't get allocated.", -2);
	prepare_semaphores();
	*data()->philos = NULL;
	get_time();
}

static void	pass_philos(void)
{
	int	i;
	int	total_meals;

	i = -1;
	total_meals = 0;
	init_philos();
	while (1)
	{
		while (++i < data()->input.p_nbr)
			data()->philos[i] = new_philo(i);
		if (data()->input.to_eat > -1)
		{
			sem_wait(data()->total_meals);
			total_meals++;
			if (total_meals == data()->input.p_nbr)
			{
				data()->init_routine = false;
				break ;
			}
		}
		else if (data()->pid != 0)
			break ;
	}
	if (total_meals != data()->input.p_nbr)
		waitpid(-1, 0, 0);
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
	data()->pid = malloc(sizeof(pid_t) * data()->input.p_nbr);
	data()->printable = true;
	data()->init_routine = true;
	data()->total_meals = 0;
	pass_philos();
}
