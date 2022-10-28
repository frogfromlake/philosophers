/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fquist <fquist@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/09 22:34:51 by fquist            #+#    #+#             */
/*   Updated: 2022/05/15 15:51:35 by fquist           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/philo_bonus.h"

static void	print_usage_exit(int error)
{
	if (error == 1)
	{
		printf("%sError:%s expected more arguments.\n", RED, RESET);
		printf("Usage >>> %s./philo%s %s\'number_of_philosophers\' \'input_to_die\'"
			" \'input_to_eat\' \'input_to_sleep\'%s optional:"
			" %s\'[number_of_inputs_each_philosopher_must_eat]\'%s\n",
			GREEN, RESET, GREEN, RESET, LGREEN, RESET);
	}
	else if (error == 2)
	{
		printf("%sError:%s too many arguments.\n", RED, RESET);
		printf("Usage >>> %s./philo%s %s\'number_of_philosophers\' \'input_to_die\'"
			" \'input_to_eat\' \'input_to_sleep\'%s optional:"
			" %s\'[number_of_inputs_each_philosopher_must_eat]\'%s\n",
			GREEN, RESET, GREEN, RESET, LGREEN, RESET);
	}
	else
	{
		printf("%sError:%s allocation failed at: '%sparser.c%s':"
			" '%sprepare_args()%s'.\nExiting.\n",
			RED, RESET, YELLOW, RESET, YELLOW, RESET);
	}
	exit(EXIT_FAILURE);
}

static char	**prepare_args(void)
{
	int		i;
	char	**arguments;

	i = 0;
	arguments = malloc(sizeof(char *) * 5);
	if (!arguments)
		return (NULL);
	while (i < 5)
	{
		if (i == 0)
			arguments[0] = ft_strdup("number_of_philosophers");
		else if (i == 1)
			arguments[1] = ft_strdup("input_to_die");
		else if (i == 2)
			arguments[2] = ft_strdup("input_to_eat");
		else if (i == 3)
			arguments[3] = ft_strdup("input_to_sleep");
		else if (i == 4)
			arguments[4]
				= ft_strdup("[number_of_inputs_each_philosopher_must_eat]");
		if (!arguments[i])
			return (NULL);
		i++;
	}
	return (arguments);
}

static void	error_condition(int argc, char **argv, char **arguments, int i)
{
	(void)argc;
	if (argv[i][0] == '-' || str_cmp(argv[i], "0"))
	{
		printf("%sError:%s can not be zero or negativ: \'%s%s%s\'\n",
			RED, RESET, YELLOW, arguments[i], RESET);
		exit(EXIT_FAILURE);
	}
	else
	{
		printf("%sError:%s non-numeric value for: \'%s%s%s\'\n",
			RED, RESET, YELLOW, arguments[i], RESET);
		exit(EXIT_FAILURE);
	}
}

static void	error_check(int argc, char **argv, char **arguments, int i)
{
	int		j;

	j = 0;
	while (i < argc)
	{
		j = 0;
		if (str_len(argv[i]) > 10 || philo_atoi(argv[i]) == INT_MAX)
		{
			printf("%sError:%s integer-overflow for: \'%s%s%s\'\n",
				RED, RESET, YELLOW, arguments[i], RESET);
			exit(EXIT_FAILURE);
		}
		while (argv[i][j])
		{
			if ((argv[i][0] != '0' && argv[i][j] >= '0' && argv[i][j] <= '9'
				&& str_len(argv[i]) > 1) || (str_len(argv[i]) == 1
				&& argv[i][j] > '0' && argv[i][j] <= '9'))
				j++;
			else
				error_condition(argc, argv, arguments, i - 1);
		}
		i++;
	}
}

void	parser(int argc, char **argv)
{
	int		i;
	char	**arguments;

	i = 1;
	if (argc < 5)
		print_usage_exit(1);
	else if (argc > 6)
		print_usage_exit(2);
	arguments = prepare_args();
	if (!arguments)
		print_usage_exit(0);
	error_check(argc, argv, arguments, i);
	if (arguments)
		free_array(arguments);
	return ;
}
