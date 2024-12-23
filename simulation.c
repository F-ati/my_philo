/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fel-aziz <fel-aziz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 12:22:57 by fel-aziz          #+#    #+#             */
/*   Updated: 2024/12/23 15:05:56 by fel-aziz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long get_time_passed_us(struct timeval pre_sleep_time)
{
	struct timeval post_sleep_time;
	long time_in_us;
	gettimeofday(&post_sleep_time,NULL);
	time_in_us =  (post_sleep_time.tv_sec * 1000000 + post_sleep_time.tv_usec) - (pre_sleep_time.tv_sec * 1000000  + pre_sleep_time.tv_usec );
	return(time_in_us);
}

long get_time_passed_mill(struct timeval start_time)
{
	struct timeval time_passed;
	long time_mill;
	gettimeofday(&time_passed,NULL);
	time_mill =  ((time_passed.tv_sec * 1000) + (time_passed.tv_usec / 1000)) - ((start_time.tv_sec * 1000) + (start_time.tv_usec / 1000));
	return(time_mill);
}

void write_action(t_data *data , char *s)
{
	pthread_mutex_lock(data->chared_mutex);
	printf("[%ld]  %d %s\n",get_time_passed_mill(data->sim_start_time),data->philo_id, s);
	pthread_mutex_unlock(data->chared_mutex);

}


void check_is_die(t_data *data)
{
	struct timeval passed_time;
	long time_in_mill;
	gettimeofday(&passed_time,NULL);
	time_in_mill =  (passed_time.tv_sec * 1000 + passed_time.tv_usec / 1000)  - (data->sim_start_time.tv_sec * 1000 + data->sim_start_time.tv_usec / 1000);
	if (time_in_mill > data->input.time_to_die)
	{
		// printf("-->%ld\n",time_in_mill);
		// printf("%d\n",data->input.time_to_die);
		pthread_mutex_lock(data->chared_mutex);
		*data->is_die = 1;
		pthread_mutex_unlock(data->chared_mutex);
	}
}
void sleep_philo(int time_must_sleep ,t_data *data)
{
	long time_to_sleep_us;
	struct timeval pre_sleep_time;
	long time_passed = 0;
	time_to_sleep_us = time_must_sleep * 1000;
	gettimeofday(&pre_sleep_time,NULL);
	while( time_passed < time_to_sleep_us)
	{
		usleep(60);
		check_is_die(data);
		pthread_mutex_lock(data->chared_mutex);
		if(*data->is_die == 1)
		{
			pthread_mutex_unlock(data->chared_mutex);
			break;
		}
		pthread_mutex_unlock(data->chared_mutex);

		time_passed = get_time_passed_us(pre_sleep_time);
	}
}
void run_single_philosopher(t_data *data)
{
	write_action(data," is thinking");
	write_action(data," has taken a fork");
	sleep_philo(data->input.time_to_die ,data);
	write_action(data," died");
}

int stop_sumulation(t_data *data)
{
	check_is_die(data);
	pthread_mutex_lock(data->chared_mutex);
	if(*data->is_die == 1 || *data->full == 1)
	{
		*data->error = data->philo_id;
		pthread_mutex_unlock(data->chared_mutex);
		return(-7);
	}
	pthread_mutex_unlock(data->chared_mutex);
	return(0);
}


void start_sumulation(t_data *data)
{
	 
	while(stop_sumulation(data) == 0)
	{
		write_action(data," is thinking");
		pthread_mutex_lock(data->left_forks);
		write_action(data," has taken a fork");
		pthread_mutex_unlock(data->right_fork);
		write_action(data , " has taken a fork");
		write_action(data," is eating");
		check_is_die(data);
		// gettimeofday(&data->sim_start_time,NULL);
		sleep_philo(data->input.time_to_eat ,data);
		pthread_mutex_lock(data->chared_mutex);
		data->meal_count = data->meal_count + 1;
		pthread_mutex_unlock(data->chared_mutex);
		if(data->input.nb_of_meals != -7 && data->meal_count >= data->input.nb_of_meals)
		{	
			pthread_mutex_lock(data->chared_mutex);
			*data->full = 1;
			pthread_mutex_unlock(data->chared_mutex);
			pthread_mutex_unlock(data->left_forks);
			pthread_mutex_unlock(data->right_fork);	
			break;
		}
		pthread_mutex_unlock(data->left_forks);
		pthread_mutex_unlock(data->right_fork);
		write_action(data, " is sleeping");
		sleep_philo(data->input.time_to_sleep ,data);
	}

}

void *simulation( void *str)
{
	t_data *data;
	data = (t_data *)str;
	gettimeofday(&data->sim_start_time,NULL);
	if (data->input.nb_of_philo == 1)
	{
		run_single_philosopher(data);
		return(NULL);
	}
	if( data->philo_id % 2 == 0)
	{
		write_action(data, " is sleeping");
		sleep_philo(data->input.time_to_sleep ,data);

	}
	start_sumulation(data);
	return(NULL);
}