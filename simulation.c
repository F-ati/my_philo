/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fel-aziz <fel-aziz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 12:22:57 by fel-aziz          #+#    #+#             */
/*   Updated: 2024/12/18 16:16:12 by fel-aziz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long get_time_passed(struct timeval pre_sleep_time)
{
	struct timeval post_sleep_time;
	long time_in_us;
	gettimeofday(&post_sleep_time,NULL);
	time_in_us =  (post_sleep_time.tv_sec * 1000000 + post_sleep_time.tv_usec) - (pre_sleep_time.tv_sec * 1000000  + pre_sleep_time.tv_usec );
	return(time_in_us);
}

void write_action(t_data *data , char *s)
{
	pthread_mutex_lock(&data->chared_mutex);
	printf(" %d %s\n",data->philo_id, s);
	pthread_mutex_unlock(&data->chared_mutex);

}

void sleep_philo(int time_must_sleep)
{
	long time_to_sleep_us;
	struct timeval pre_sleep_time;
	long time_passed = 0;
	time_to_sleep_us = time_must_sleep * 1000;
	gettimeofday(&pre_sleep_time,NULL);
	while( time_passed < time_to_sleep_us)
	{
		usleep(60);
		// if sume philo is die
		time_passed = get_time_passed(pre_sleep_time);
	}
}

void run_single_philosopher(t_data *data)
{
	write_action(data," is thinking");
	write_action(data," has taken a fork");
	sleep_philo(data->input.time_to_die);
	write_action(data," died");
}
void check_is_die(t_data *data)
{
	struct timeval passed_time;
	long time_in_mill;
	gettimeofday(&passed_time,NULL);
	time_in_mill =  (passed_time.tv_sec * 1000 + passed_time.tv_usec / 1000)  - (data->last_meal_time.tv_sec * 1000 + data->last_meal_time.tv_usec / 1000);
	if (time_in_mill >= data->input.time_to_die)
	{
		pthread_mutex_lock(&data->chared_mutex);
		*data->is_die = 1;
		pthread_mutex_unlock(&data->chared_mutex);
	}
}

int stop_sumulation(t_data *data)
{
	pthread_mutex_lock(&data->chared_mutex);
	check_is_die(data);
	if(*data->is_die == 1 || *data->full == 1)
	{
		// *data->error = data->philo_id;
		pthread_mutex_unlock(&data->chared_mutex);
		return(-7);
	}
	pthread_mutex_unlock(&data->chared_mutex);
	return(0);
}


void start_sumulation(t_data *data)
{
	gettimeofday(&data->last_meal_time , NULL);
	while(stop_sumulation(data) == 0)
	{
		write_action(data," is thinking");
		pthread_mutex_lock(data->left_forks);
		write_action(data," has taken a fork");
		pthread_mutex_unlock(data->right_fork);
		write_action(data , " has taken a fork");
		write_action(data," is eating");
		gettimeofday(&data->last_meal_time , NULL);
		sleep_philo(data->input.time_to_eat);
		pthread_mutex_lock(&data->chared_mutex);
		data->meal_count = data->meal_count + 1;
		pthread_mutex_unlock(&data->chared_mutex);
		if(data->meal_count >= data->input.nb_of_meals)
		{	
			pthread_mutex_lock(&data->chared_mutex);
			// *data->full = 1;
			break;
			pthread_mutex_unlock(&data->chared_mutex);
		}
		pthread_mutex_unlock(data->left_forks);
		pthread_mutex_unlock(data->right_fork);
		write_action(data, " is sleeping");
		sleep_philo(data->input.time_to_sleep);
	}

}

void *simulation( void *str)
{
	t_data *data;
	data = (t_data *)str;
	if (data->input.nb_of_philo == 1)
	{
		run_single_philosopher(data);
		return(NULL);
	}
	if( data->philo_id % 2 == 0)
	{
		write_action(data, " is sleeping");
		sleep_philo(data->input.time_to_sleep);

	}
	start_sumulation(data);
	return(NULL);

}