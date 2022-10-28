/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fquist <fquist@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/10 16:49:49 by fquist            #+#    #+#             */
/*   Updated: 2022/05/15 17:24:22 by fquist           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

/* ************************************************************************** */
/* STANDARD INCLUDES														  */
/* ************************************************************************** */
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <pthread.h>
# include <stdbool.h>
# include <sys/time.h>
# include <limits.h>

/* ************************************************************************** */
/* 	DEFINES																	  */
/* ************************************************************************** */
# define BLACK	"\033[0;30m"
# define RED	"\033[0;31m"
# define RED_B	"\033[1;31m"
# define GREEN	"\033[1;32m"
# define LGREEN	"\033[0;32m"
# define YELLOW	"\033[0;33m"
# define BLUE	"\033[0;34m"
# define PURPLE	"\033[0;35m"
# define CYAN	"\033[0;36m"
# define WHITE	"\033[0;37m"
# define RESET	"\e[0m"

/* ************************************************************************** */
/* 	PARSER																	  */
/* ************************************************************************** */
void	parser(int argc, char **argv);
int		philo_atoi(const char *str);
void	free_array(char **array);
int		str_len(const char *str);
char	*ft_strdup(const char *s1);

/* ************************************************************************** */
/* 	DATA STRUCTURES															  */
/* ************************************************************************** */
typedef pthread_mutex_t	t_mutex;

enum e_status {
	thinking,
	sleeping,
	waiting,
	lonely
};

typedef struct s_philo
{
	pthread_t	th_id;
	t_mutex		lock_fork;
	time_t		last_meal;
	bool		dead;
	bool		fork;
	int			id;
	int			status;
	int			meals;
	int			t_meals;
}	t_philo;

typedef struct s_input
{
	int				p_nbr;
	int				to_eat;
	time_t			ttd;
	time_t			tte;
	time_t			tts;
}	t_input;

typedef struct s_data
{
	t_mutex	print;
	t_mutex	init_lock;
	t_mutex	status_lock;
	t_mutex	eaten;
	t_philo	**philos;
	t_input	input;
	time_t	starttime;
	bool	printable;
	bool	init_routine;
	int		th_nbr;
}	t_data;

t_data	*data(void);
t_philo	*new_philo(int i);
void	init_philos(void);
void	init_data(char **argv);

/* ************************************************************************** */
/* 	TIMES																	  */
/* ************************************************************************** */
time_t	get_time(void);
void	sleep_ms(t_philo *philo, time_t val);
void	time_to_die(t_philo *philo);

/* ************************************************************************** */
/* 	Threads																	  */
/* ************************************************************************** */
void	join_threads(void);
bool	init_routine(void);
void	*routine(void *varg);
void	eating(t_philo *philo);
void	take_forks(t_philo *philo, int id);
void	take_one_fork(t_philo *philo, t_philo *check);
void	eating(t_philo *philo);

/* ************************************************************************** */
/* 	Utils																	  */
/* ************************************************************************** */
void	print_msg(int id, char *str);
void	error_msg(char *str, int i);
int		str_cmp(const char *s1, const char *s2);

#endif
