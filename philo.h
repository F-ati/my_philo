/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fel-aziz <fel-aziz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/14 13:42:02 by fel-aziz          #+#    #+#             */
/*   Updated: 2024/12/16 17:41:09 by fel-aziz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
#define PHILO_H

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/time.h>

typedef struct s_input
{
	int nb_of_philo;
	int time_to_die;
	int time_to_eat;
	int time_to_sleep;
	int nb_of_meals;
}t_input;

typedef struct s_philo
{
	
} t_philo;

typedef struct s_forks
{

}t_forks;

typedef struct s_data
{
	t_input input;
	// t_philo *philos;
	// t_forks *forks;
	pthread_mutex_t chare_mutex;
	int	*error;
	int *full;
	int *is_die;
	int *p1;
	int *p2;
	int *p3;
	
}t_data ;


int	check_is_number(char *str);
int	ft_atoi(char *str);
int	allocate_data(t_data **data,pthread_t **philo, pthread_mutex_t **forks,
		int nb_of_philo);
void init_iput(t_data *data ,char **av ,int nb);
void initialize_data( t_data *data,char *av[]);
int initialize_mutex(t_data *data ,pthread_mutex_t *forks);




#endif