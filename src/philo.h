/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slord <slord@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 11:25:46 by slord             #+#    #+#             */
/*   Updated: 2022/11/23 22:08:33 by slord            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct s_table
{
	int				nb_philo;
	pthread_mutex_t	*mutex;
	pthread_t		*threads_philo;
	time_t			time_to_eat;
	pthread_mutex_t	waiter;
	time_t			time_without_meal;
	time_t			time_to_sleep;
	int				nb_of_meals;
	int				meals;
	time_t			start_time;
	struct s_philo	*philo;
}		t_table;

typedef struct s_philo
{
	int				n_philo;
	t_table			*table;
	int				meals;
	time_t			time_last_meal;
	pthread_t		thread;
	int				fork_1;
	int				fork_2;
}		t_philo;

int		start(void);
int		init_table(int argc, char **argv);
int		check_args(int argc, char **argv);
t_table	*get_struc_table(void);
void	take_fork(int pos, t_philo philo);
int		init_mutex(void);
int		init_philo(void);
void	*routine_philo(void *arg);
void	eating(t_philo *philo, int pos1, int pos2);
void	sleeping(t_philo philo);
void	thinking(t_philo *philo);
int		death_watcher(void);
time_t	get_time(void);
void	goodnight_sweetprince(t_philo philo, time_t time_to_sleep);
int		free_table(void);
int		ft_atoi(const char *str);
void	ft_putstr_fd(char *s, int fd);
int		ft_isdigit(int c);
#endif