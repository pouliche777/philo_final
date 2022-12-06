/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_death.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slord <slord@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 15:01:33 by slord             #+#    #+#             */
/*   Updated: 2022/11/23 22:16:39 by slord            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	detatch_threads(t_philo *philo)
{
	int	i;

	i = 0;
	while (i < philo->table->nb_philo)
	{
		pthread_detach(philo[i].thread);
		i++;
	}
}

int	print_death(t_philo *philo, int i)
{
	if (philo->table->nb_philo == 1)
	{
		goodnight_sweetprince(philo[i], philo->table->time_without_meal);
		pthread_mutex_lock(&philo->table->waiter);
		printf(" %lu  philosopher %d died\n", get_time()
			- philo[i].table->start_time, philo[i].n_philo + 1);
		return (0);
	}
	if ((get_time() - philo[i].table->start_time - philo[i].time_last_meal)
		>= philo[i].table->time_without_meal)
	{
		if (philo[i].meals != philo->table->nb_of_meals)
		{
			pthread_mutex_lock(&philo->table->waiter);
			printf(" %lu  philosopher %d died\n", get_time()
				- philo[i].table->start_time, philo[i].n_philo + 1);
			detatch_threads(philo);
			return (0);
		}
	}
	return (1);
}

int	death_watcher(void)
{
	t_table	*table;
	t_philo	*philo;
	int		i;

	table = get_struc_table();
	philo = table->philo;
	i = 0;
	while (1)
	{
		if (philo[i].table->meals == philo[i].table->nb_of_meals
			* philo[i].table->nb_philo)
			break ;
		if (print_death(philo, i) == 0)
			return (0);
		i++;
		if (i == philo->table->nb_philo)
			i = 0;
		usleep(10);
	}
	return (1);
}

int	free_table(void)
{
	int		i;
	t_table	*table;

	table = get_struc_table();
	i = 0;
	while (i < table->nb_philo)
	{
		pthread_mutex_destroy(&table->mutex[i]);
		i++;
	}
	pthread_mutex_destroy(&table->waiter);
	free(table->philo);
	free(table->threads_philo);
	free(table->mutex);
	free(table);
	return (0);
}	
