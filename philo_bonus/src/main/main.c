/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fquist <fquist@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 22:22:57 by fquist            #+#    #+#             */
/*   Updated: 2022/05/15 16:10:22 by fquist           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/philo_bonus.h"

void	wait_for_prcs(void)
{
	int	i;

	i = -1;
	while (++i < data()->input.p_nbr)
		kill(data()->pid[i], SIGINT);
	i = -1;
	while (++i < data()->input.p_nbr)
	{
		if (data()->philos[i])
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

int	main(int argc, char **argv)
{
	parser(argc, argv);
	init_data(argv);
	wait_for_prcs();
	return (0);
}
