/**
 * The entrypoint of the homework. Every initialization must be done here
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "feed.h"
#include "friends.h"
#include "posts.h"
#include "users.h"

/**
 * Initializez every task based on which task we are running
 */
void init_tasks(void)
{
#ifdef TASK_1

#endif

#ifdef TASK_2

#endif

#ifdef TASK_3

#endif
}

int **init_adj_mat(void)
{
	int **adj_mat = calloc(518, sizeof(int *));
	for (int i = 0; i < 518; i++)
		adj_mat[i] = calloc(518, sizeof(int));

	return adj_mat;
}

/**
 * Entrypoint of the program, compiled with different defines for each task
 */

int main(void)
{
	init_users();

	init_tasks();

	char *input = (char *)malloc(MAX_COMMAND_LEN);
	char *aux = NULL;

	// Initialize the adjacency matrix
	#if defined(TASK_1) || defined(TASK_3)
	int **adj_mat = init_adj_mat();
	int *no_friends = calloc(518, sizeof(int));
	#endif

	// Initialize the post counter and array
	#if defined(TASK_2) || defined(TASK_3)
	post_array_t *posts = calloc(1, sizeof(post_array_t));
	posts->array = calloc(100, sizeof(post_t *));
	posts->size = 0;
	posts->capacity = 100;
	#endif

	while (1) {
		aux = fgets(input, MAX_COMMAND_LEN, stdin);

		// If fgets returns null, we reached EOF
		if (!aux)
			break;

		#ifdef TASK_1
		handle_input_friends(input, adj_mat, no_friends);
		#endif

		#ifdef TASK_2
		handle_input_posts(input, posts);
		#endif

		#ifdef TASK_3
		handle_input_feed(input);
		#endif
	}
	#if defined(TASK_1) || defined(TASK_3)
	for (int i = 0; i < 518; i++)
		free(adj_mat[i]);
	free(adj_mat);
	free(no_friends);
	#endif

	#if defined(TASK_2) || defined(TASK_3)
	// Free posts array and its contents
	free_posts(posts);
	#endif
	free(input);
	free_users();
	return 0;
}
