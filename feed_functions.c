#include "feed_functions.h"
#include "feed.h"
#include "posts.h"
#include "users.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void feed(char *input, int **adj_mat, post_array_t *posts)
{
    // Parse the input
	strtok(input, " ");
	char *user = strtok(NULL, " ");
	char *feed_size = strtok(NULL, "\n");

    // Get the user id and feed size
	int feed_size_int = atoi(feed_size);
	int user_id = get_user_id(user);
	int count = 0;
	int *friends = adj_mat[user_id];

    // Go through the posts in reverse order to print the most recent ones
    // first, and print the posts of the user and his friends
	for (int i = posts->size - 1; i >= 0 && count < feed_size_int; i--) {
		if (posts->array[i]->user_id == user_id) {
			if (posts->array[i]->title) {
				printf("%s: \"%s\"\n", get_user_name(posts->array[i]->user_id),
					   posts->array[i]->title);
				count++;
			}
		} else {
			for (int j = 0; j < MAX_USERS; j++) {
				if (friends[j] == 1 && posts->array[i]->user_id == j &&
					posts->array[i]->title) {
					printf("%s: \"%s\"\n",
						   get_user_name(posts->array[i]->user_id),
						   posts->array[i]->title);
					count++;
					break;
				}
			}
		}
	}
}

void view_profile(char *input, post_array_t *posts)
{
    // Parse the input
	strtok(input, " ");
	char *user = strtok(NULL, "\n");

    // Get the user id
	int user_id = get_user_id(user);

    // Print the posts of the user
	for (unsigned int i = 0; i < posts->size; i++) {
		if (posts->array[i]->user_id == user_id) {
			int parent_id = posts->array[i]->parent_post_id - 1;
			if (posts->array[i]->title)
				printf("Posted: \"%s\"\n", posts->array[i]->title);
			else
				printf("Reposted: \"%s\"\n", posts->array[parent_id]->title);
		}
	}
}

void friends_repost(char *input, int **adj_mat, post_array_t *posts)
{
    // Parse the input
	strtok(input, " ");
	char *user = strtok(NULL, " ");
	char *post_id = strtok(NULL, "\n");

    // Get the user id and the post id
	int user_id = get_user_id(user);
	int post_id_int = atoi(post_id);

    // Print the posts of the friends that reposted the post
	for (unsigned int i = 0; i < posts->size; i++)
		if (posts->array[i]->parent_post_id == post_id_int)
			for (int j = 0; j < MAX_USERS; j++)
				if (adj_mat[user_id][j] == 1 && posts->array[i]->user_id == j)
					printf("%s\n", get_user_name(j));
}

static int is_clique(int *group, int group_size, int **adj_mat)
{
    // Check if the group is a clique
	for (int i = 0; i < group_size; i++)
		for (int j = i + 1; j < group_size; j++)
			if (adj_mat[group[i]][group[j]] == 0)
				return 0;
	return 1;
}

static void find_cliques(int *current_clique, int current_size,
						 int start, int user_id, int max_users, int **adj_mat,
						 int *best_clique, int *best_clique_size)
{
    // Check if the current group is a clique and update the best clique
	if (is_clique(current_clique, current_size, adj_mat)) {
		if (current_size > *best_clique_size) {
			*best_clique_size = current_size;
			memcpy(best_clique, current_clique, current_size * sizeof(int));
		}
	}

    // Recursively find cliques
	for (int i = start; i < max_users; i++) {
		if (adj_mat[user_id][i] == 1 || i == user_id) {
			current_clique[current_size] = i;
			find_cliques(current_clique, current_size + 1, i + 1,
						 user_id, max_users, adj_mat, best_clique,
						 best_clique_size);
		}
	}
}

void common_groups(char *input, int **adj_mat)
{
    // Parse the input
	strtok(input, " ");
	char *user = strtok(NULL, "\n");

    // Get the user id
	int user_id = get_user_id(user);

    // Find the closest friend group of the user
	int *best_clique = malloc(MAX_USERS * sizeof(int));
	int best_clique_size = 0;

	int *current_clique = malloc(MAX_USERS * sizeof(int));

	current_clique[0] = user_id;
	find_cliques(current_clique, 1, 0, user_id, MAX_USERS, adj_mat,
				 best_clique, &best_clique_size);

    // Sort the names of the users in the group
	for (int i = 0; i < best_clique_size; i++) {
		for (int j = i + 1; j < best_clique_size; j++) {
			if (best_clique[i] > best_clique[j]) {
				int temp = best_clique[i];
				best_clique[i] = best_clique[j];
				best_clique[j] = temp;
			}
		}
	}

	printf("The closest friend group of %s is:\n", user);
	for (int i = 0; i < best_clique_size; i++)
		printf("%s\n", get_user_name(best_clique[i]));

	free(current_clique);
	free(best_clique);
}

