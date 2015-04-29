#include <stdio.h>
#include <pthread.h>
#include <errno.h>
#include "recmutex.h"

int recursive_mutex_init (recursive_mutex_t *mu)
{
	if (mu == NULL) return 1;

	if (pthread_mutex_init(&(mu->mutex), NULL)) return 2;
	if (pthread_cond_init(&(mu->cond), NULL)) return 3;
	mu->count = 0;
	mu->wait_count = 0;
	return 0;
}

int recursive_mutex_destroy (recursive_mutex_t *mu)
{
	if (mu == NULL) return 1;

	if (pthread_mutex_destroy(&mu->mutex)) return 2;
	if (pthread_cond_destroy(&(mu->cond))) return 3;
	mu->count = 0;
	mu->wait_count = 0;
	return 0;
}

//#define switch
int recursive_mutex_lock (recursive_mutex_t *mu)
{
	int ret = 0;
	if (pthread_self() != mu->owner) {
		ret = pthread_mutex_lock(&mu->mutex);
		mu->owner = pthread_self();
		mu->count = 1;
	}
	else
		mu->count++;
	return ret;
}

int recursive_mutex_unlock (recursive_mutex_t *mu)
{
	if (pthread_self() != mu->owner)
		return 1;

	if (--(mu->count) <= 0) {
		mu->owner = 0;
		return pthread_mutex_unlock(&(mu->mutex));
	}

	return 0;
}
