/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   synchro.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajorge-p <ajorge-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 14:47:16 by ajorge-p          #+#    #+#             */
/*   Updated: 2024/05/02 17:47:33 by ajorge-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	wait_all_threads(t_table *table)
{
	while (!get_bool(&table->table_mutex, &table->all_threads_ready))
		;
}

bool	all_threads_running(t_mtx *mtx, long *threads, long philo_nbr)
{
	bool	ret;

	ret = false;
	safe_mutex(mtx, LOCK);
	if (*threads == philo_nbr)
		ret = true;
	safe_mutex(mtx, UNLOCK);
	return (ret);
}

void	increment_long(t_mtx *mtx, long *value)
{
	safe_mutex(mtx, LOCK);
	(*value)++;
	safe_mutex(mtx, UNLOCK);
}

void	dsynchronize_philos(t_philo *philo)
{
	if (philo->table->philo_nbr % 2 == 0)
	{
		if (philo->id % 2 == 0)
			precise_usleep(30000, philo->table);
	}
	else
	{
		if (philo->id % 2)
			thinking(philo, true);
	}
}
