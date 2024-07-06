/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajorge-p <ajorge-p@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 14:46:56 by ajorge-p          #+#    #+#             */
/*   Updated: 2024/05/03 12:03:45 by ajorge-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

bool	dead_philo(t_philo *philo)
{
	long	elapsed;
	long	time_to_die;

	if (get_bool(&philo->philo_mutex, &philo->full))
		return (false);
	time_to_die = philo->table->time_to_die / 1000;
	elapsed = gettime(MILLISECONDS) - get_long(&philo->philo_mutex,
			&philo->last_meal_time);
	if (elapsed > time_to_die)
		return (true);
	return (false);
}

void	*monitor_dinner(void *data)
{
	t_table	*table;
	int		i;

	table = (t_table *)data;
	while (!all_threads_running(&table->table_mutex,
			&table->nbr_threads_running, table->philo_nbr))
		;
	while (!simulation_finished(table))
	{
		i = -1;
		while (++i < table->philo_nbr && !simulation_finished(table))
		{
			if (dead_philo(table->philos + i))
			{
				write_status(DIED, table->philos + i, DEBUG_MODE);
				set_bool(&table->table_mutex, &table->end_sim, true);
			}
		}
	}
	return (NULL);
}
