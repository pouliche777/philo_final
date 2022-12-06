/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slord <slord@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 15:59:03 by slord             #+#    #+#             */
/*   Updated: 2022/11/23 22:06:09 by slord            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	start(void)
{
	if (init_mutex() == 0)
		return (0);
	if (init_philo() == 0)
		return (0);
	return (1);
}

int	init_mutex(void)
{
	t_table	*table;
	int		i;

	table = get_struc_table();
	i = 0;
	table->mutex = malloc(sizeof(pthread_mutex_t) * table->nb_philo);
	while (i < table->nb_philo)
	{
		pthread_mutex_init(&table->mutex[i], NULL);
		i++;
	}
	if (pthread_mutex_init(&table->waiter, NULL) != 0)
		return (0);
	return (1);
}

int	init_philo(void)
{
	int			i;
	t_table		*table;

	i = -1;
	table = get_struc_table();
	table->threads_philo = malloc(sizeof(pthread_t) * table->nb_philo);
	table->philo = malloc(sizeof(t_philo) * table->nb_philo);
	table->start_time = get_time();
	while (++i < table->nb_philo)
	{
		table->philo[i].n_philo = i;
		table->philo[i].table = table;
		table->philo[i].time_last_meal = 0;
		table->philo[i].thread = table->threads_philo[i];
		table->philo[i].meals = 0;
	}
	i = -1;
	while (++i < table->nb_philo)
	{
		if (pthread_create(&table->threads_philo[i],
				NULL, &routine_philo, &table->philo[i]) != 0)
			return (0);
	}
	return (1);
}

void	*routine_philo(void *arg)
{	
	t_philo	*philo;
	int		pos;

	philo = (t_philo *)arg;
	if (philo->n_philo % 2 == 0)
		usleep(3000);
	pos = philo->n_philo;
	philo->fork_1 = pos;
	philo->fork_2 = pos + 1;
	if (philo->fork_2 == philo->table->nb_philo)
			philo->fork_2 = 0;
	while (1)
	{
		if (!philo)
			return (0);
		if (philo->meals == philo->table->nb_of_meals)
			return (0);
		take_fork(philo->fork_1, *philo);
		take_fork(philo->fork_2, *philo);
		eating(philo, philo->fork_2, philo->fork_1);
		sleeping(*philo);
		thinking(philo);
	}
	return (0);
}

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	else
		return (0);
}
