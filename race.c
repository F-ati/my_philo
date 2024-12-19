/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   race.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fel-aziz <fel-aziz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 11:47:52 by fel-aziz          #+#    #+#             */
/*   Updated: 2024/12/19 12:20:17 by fel-aziz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/time.h>

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

pthread_mutex_t mutex;  // Shared mutex

void *sum2(void *str) {
    int *s = (int *)str;

    while (1) {
        pthread_mutex_lock(&mutex);  // Lock the shared mutex
        *s = 1;  // Modify the shared variable
        pthread_mutex_unlock(&mutex);  // Unlock the shared mutex
    }
    return NULL;
}

void *sum1(void *str) {
    int *s = (int *)str;

    while (1) {
        pthread_mutex_lock(&mutex);  // Lock the shared mutex
        *s = 1;  // Modify the shared variable
        pthread_mutex_unlock(&mutex);  // Unlock the shared mutex
    }
    return NULL;
}

int main() {
    pthread_t t1, t2;
    int *p1 = malloc(sizeof(int));
    *p1 = 0;
    if (pthread_mutex_init(&mutex, NULL) != 0) {  // Initialize the shared mutex
        printf("Mutex initialization failed\n");
        return 1;
    }
	


    // Create threads
    pthread_create(&t1, NULL, sum1, p1);
    pthread_create(&t2, NULL, sum2, p1);

    // Wait for threads to finish
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    pthread_mutex_destroy(&mutex);  // Destroy the shared mutex
    free(p1);  // Free allocated memory

    return 0;
}
