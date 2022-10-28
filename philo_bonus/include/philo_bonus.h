/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fquist <fquist@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/10 16:49:49 by fquist            #+#    #+#             */
/*   Updated: 2022/05/15 16:01:19 by fquist           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

/* ************************************************************************** */
/* STANDARD INCLUDES														  */
/* ************************************************************************** */
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdbool.h>
# include <sys/time.h>
# include <signal.h>
# include <semaphore.h>
# include <pthread.h>
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

# define TOTAL_MEALS	"/total_meals"
# define LOCK_FORK		"/lock_fork"
# define PRINT			"/print"
# define INIT_LOCK		"/init_lock"
# define EATEN			"/eaten"
# define STATUS_LOCK	"/status_lock"
# define START			"/start"

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
enum e_status {
	thinking,
	sleeping,
	waiting,
	lonely
};

typedef struct s_philo
{
	pid_t	th_id;
	time_t	last_meal;
	bool	fork;
	int		id;
	int		status;
	int		meals;
}	t_philo;

typedef struct s_input
{
	int				p_nbr;
	time_t			ttd;
	time_t			tte;
	time_t			tts;
	int				to_eat;
}	t_input;

typedef struct s_data
{
	sem_t		*lock_fork;
	sem_t		*print;
	sem_t		*init_lock;
	sem_t		*status_lock;
	sem_t		*eaten;
	sem_t		*total_meals;
	t_philo		**philos;
	t_input		input;
	pid_t		*pid;
	bool		printable;
	bool		init_routine;
}	t_data;

t_data	*data(void);
void	init_data(char **argv);

/* ************************************************************************** */
/* 	Times																	  */
/* ************************************************************************** */
time_t	get_time(void);
void	sleep_ms(time_t val);

/* ************************************************************************** */
/* 	Processes																  */
/* ************************************************************************** */
void	routine(t_philo *philo, t_data *data);
void	eating(t_philo *philo, t_data *data);
void	wait_for_prcs(void);

/* ************************************************************************** */
/* 	Utils																	  */
/* ************************************************************************** */
void	print_msg(int id, char *str, t_data *data);
void	error_msg(char *str, int i);
bool	check_meals(t_philo *philo);
int		str_cmp(const char *s1, const char *s2);

/* ************************************************************************** */
/* 	Reaper 																	  */
/* ************************************************************************** */
int		reaper_awake(t_philo *philo, int i);

#endif
