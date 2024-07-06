/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   safe_funcs.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajorge-p <ajorge-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 13:27:14 by ajorge-p          #+#    #+#             */
/*   Updated: 2024/05/07 17:41:17 by ajorge-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	*safe_malloc(size_t bytes)
{
	void	*ret;

	ret = malloc(bytes);
	if (!ret)
		error_exit("Error on Malloc\n");
	return (ret);
}

void	handle_error_mutex(int status, t_opcode opcode)
{
	if (status == 0)
		return ;
	if (status == EINVAL && (opcode == LOCK || opcode == UNLOCK
			|| opcode == DESTROY))
		error_exit("The value specified by mutex is invalid.");
	else if (status == EINVAL && opcode == INIT)
		error_exit("The value specified by attr is invalid.");
	else if (status == EDEADLK)
		error_exit("A deadlock would occur if the thread"
			"blocked waiting for mutex.");
	else if (status == EPERM)
		error_exit("The current thread does not hold a lock on mutex.");
	else if (status == ENOMEM)
		error_exit ("The process cannot allocate enough memory"
			"to create another mutex.");
	else if (status == EBUSY)
		error_exit("Mutex is locked");
}

void	safe_mutex(t_mtx *mutex, t_opcode opcode)
{
	if (opcode == LOCK)
		handle_error_mutex(pthread_mutex_lock(mutex), opcode);
	else if (opcode == UNLOCK)
		handle_error_mutex(pthread_mutex_unlock(mutex), opcode);
	else if (opcode == DESTROY)
		handle_error_mutex(pthread_mutex_destroy(mutex), opcode);
	else if (opcode == INIT)
		handle_error_mutex(pthread_mutex_init(mutex, NULL), opcode);
	else
		error_exit("Wrong opcode for mutex\n");
}

void	handle_error_thread(int status, t_opcode opcode)
{
	if (status == 0)
		return ;
	if (status == EAGAIN)
		error_exit("No resources to create another thread");
	else if (status == EPERM)
		error_exit("The caller does not have apporpriate permission\n");
	else if (status == EINVAL && opcode == CREATE)
		error_exit("The value specified by attr is invalid.");
	else if (status == EINVAL && (opcode == CREATE || opcode == DETACH))
		error_exit("The value specified by thread is not joinable\n");
	else if (status == ESRCH)
		error_exit("No thread could be found corresponding to that"
			"specified by the given threadh ID\n");
	else if (status == EDEADLK)
		error_exit("A deadlock was detected or the value of"
			"thread specifies the calling thread.\n");
	return ;
}

void	safe_thread(pthread_t *thread, void *(*foo)(void *),
		void *data, t_opcode opcode)
{
	if (opcode == CREATE)
		handle_error_thread(pthread_create(thread, NULL, foo, data), opcode);
	else if (opcode == JOIN)
		handle_error_thread(pthread_join(*thread, NULL), opcode);
	else if (opcode == DETACH)
		handle_error_thread(pthread_detach(*thread), opcode);
	else
		error_exit("Wrong opcode for thread\n");
	return ;
}
