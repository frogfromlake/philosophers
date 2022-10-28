/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fquist <fquist@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 22:22:57 by fquist            #+#    #+#             */
/*   Updated: 2022/05/10 16:21:12 by fquist           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/philo.h"

void	free_data(void)
{
	int	i;

	i = -1;
	while (++i < data()->th_nbr)
	{
		if (pthread_mutex_destroy(&data()->philos[i]->lock_fork) != 0)
			error_msg("Error: couldn't destroy Mutex", i);
	}
	if (pthread_mutex_destroy(&data()->print) != 0)
		error_msg("Error: couldn't destroy Mutex", i);
	if (pthread_mutex_destroy(&data()->init_lock) != 0)
		error_msg("Error: couldn't destroy Mutex", i);
	i = -1;
	while (++i < data()->th_nbr)
	{
		free(data()->philos[i]);
		data()->philos[i] = NULL;
	}
	free(data()->philos);
	data()->philos = NULL;
}

t_data	*data(void)
{
	static t_data	data;

	return (&data);
}

void	join_threads(void)
{
	int	i;

	i = 0;
	while (i < data()->th_nbr)
	{
		if (pthread_join(data()->philos[i]->th_id, NULL) != 0)
			error_msg("Error: couldn't join threads.", i);
		i++;
	}
}

int	main(int argc, char **argv)
{
	parser(argc, argv);
	init_data(argv);
	if (data()->philos)
		free_data();
	return (0);
}
