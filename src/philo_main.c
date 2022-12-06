/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slord <slord@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 15:00:59 by slord             #+#    #+#             */
/*   Updated: 2022/10/19 16:33:56 by slord            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_table	*get_struc_table(void)
{
	static t_table	*table = NULL;

	if (table == NULL)
		table = malloc(sizeof(t_table));
	return (table);
}

int	check_args(int argc, char **argv)
{
	int	i;
	int	j;

	j = 0;
	i = 1;
	if (argc != 5 && argc != 6)
		return (0);
	while (i < argc)
	{
		while (argv[i][j])
		{
			if (!ft_isdigit(argv[i][j]))
				return (0);
			j++;
		}
		j = 0;
		i++;
	}
	return (1);
}

int	init_table(int argc, char **argv)
{
	t_table	*table;

	table = get_struc_table();
	table->nb_philo = ft_atoi(argv[1]);
	table->time_to_eat = ft_atoi(argv[3]);
	table->time_without_meal = ft_atoi(argv[2]);
	table->time_to_sleep = ft_atoi(argv[4]);
	table->meals = 0;
	table->nb_of_meals = 0;
	table->start_time = 0;
	if (argc == 6)
		table->nb_of_meals = ft_atoi(argv[5]);
	else
		table->nb_of_meals = -1;
	return (1);
}

int	main(int argc, char **argv)
{	
	t_table	*table;
	int		i;

	if (!check_args(argc, argv))
	{
		ft_putstr_fd("wrong arguments!", 2);
		return (1);
	}
	init_table(argc, argv);
	start();
	if (!death_watcher())
	{
		free_table();
		return (0);
	}
	table = get_struc_table();
	i = -1;
	while (++i < table->nb_philo)
	{
		if (pthread_join(table->threads_philo[i], NULL) != 0)
			return (2);
	}
	free_table();
	return (0);
}
