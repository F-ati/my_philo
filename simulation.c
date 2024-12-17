/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fel-aziz <fel-aziz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 12:22:57 by fel-aziz          #+#    #+#             */
/*   Updated: 2024/12/17 14:59:41 by fel-aziz         ###   ########.fr       */
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
	printf(" %d %s\n",data->philo_id, s);
}

void sleep_philo(t_data  *data)
{
	(void)data;
	struct timeval pre_sleep_time;
	long time_passed;
	gettimeofday(&pre_sleep_time,NULL);
	usleep(100);
	time_passed = get_time_passed(pre_sleep_time);
	printf("%ld\n",time_passed);
	
}

void *simulation( void *str)
{
	t_data *data;
	data = (t_data *)str;
	if (data->input.nb_of_philo == 1)
	{
		// run_single_philosopher(data);
		return(NULL);
	}
	if( data->philo_id % 2 == 0)
	{
		write_action(data, "is sleeping");
		sleep_philo(data);

	}
	// start_sumulation();
	return(NULL);

}