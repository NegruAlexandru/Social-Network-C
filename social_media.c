/**
 * The entrypoint of the homework. Every initialization must be done here
*/
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "users.h"
#include "friends.h"
#include "posts.h"
#include "feed.h"

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

int ** init_adj_mat(void)
{
	int **adj_mat = calloc(520, sizeof(int*));
	for(int i = 0; i < 520; i++)
		adj_mat[i] = calloc(520, sizeof(int));

	return adj_mat;
}

/**
 * Entrypoint of the program, compiled with different defines for each task
*/

//main scris ca pula
int main(void)
{
	init_users();

	init_tasks();

	char *input = (char *)malloc(MAX_COMMAND_LEN);

	// Initialize the adjacency matrix
	int **adj_mat = init_adj_mat();
	int *no_friends = calloc(520, sizeof(int));

	while (1) {
		input = fgets(input, MAX_COMMAND_LEN, stdin);

		// If fgets returns null, we reached EOF
		if (!input)
			break;

		#ifdef TASK_1
		handle_input_friends(input, adj_mat, no_friends);
		#endif

		#ifdef TASK_2
		handle_input_posts(input);
		#endif

		#ifdef TASK_3
		handle_input_feed(input);
		#endif
		for(int i = 0; i < 520; i++)
			free(adj_mat[i]);
		free(adj_mat);
		free(no_friends);
	}

	return 0;
}
