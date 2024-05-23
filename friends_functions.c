//
// Created by Alex on 14/05/2024.
//

#include "friends_functions.h"
#include "users.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void add_friend(char *input, int **adj_mat, int *no_friends)
{
	// parse the input
	strtok(input, " ");
	char *user1 = strtok(NULL, " ");
	char *user2 = strtok(NULL, "\n");

	// get the user ids
	int id1 = get_user_id(user1);
	int id2 = get_user_id(user2);

	// add the connection
	adj_mat[id1][id2] = 1;
	adj_mat[id2][id1] = 1;

	// update the number of friends for each user
	no_friends[id1]++;
	no_friends[id2]++;

	printf("Added connection %s - %s\n", user1, user2);
}

void remove_friend(char *input, int **adj_mat, int *no_friends)
{
	// parse the input
	strtok(input, " ");
	char *user1 = strtok(NULL, " ");
	char *user2 = strtok(NULL, "\n");

	// get the user ids
	int id1 = (int)get_user_id(user1);
	int id2 = (int)get_user_id(user2);

	// remove the connection
	adj_mat[id1][id2] = 0;
	adj_mat[id2][id1] = 0;

	// update the number of friends for each user
	no_friends[id1]--;
	no_friends[id2]--;

	printf("Removed connection %s - %s\n", user1, user2);
}

static int *distance_compute(int id, int **adj_mat)
{
	// initialize the visited and distance arrays
	int *visited = calloc(MAX_USERS, sizeof(int));
	int *distance = calloc(MAX_USERS, sizeof(int));

	int *queue = calloc(MAX_USERS, sizeof(int));
	int front = 0, rear = 0;

	queue[rear++] = id;
	visited[id] = 1;

	while (front < rear) {
		int node = queue[front++];
		for (int i = 0; i < MAX_USERS; i++) {
			if (adj_mat[node][i] && !visited[i]) {
				queue[rear++] = i;
				visited[i] = 1;
				distance[i] = distance[node] + 1;
			}
		}
	}
	
	free(visited);
	free(queue);
	return distance;
}

void distance_between_friends(char *input, int **adj_mat)
{
	// parse the input
	strtok(input, " ");
	char *user1 = strtok(NULL, " ");
	char *user2 = strtok(NULL, "\n");

	// get the user ids
	int id1 = get_user_id(user1);
	int id2 = get_user_id(user2);

	// compute the distance
	int *distance = distance_compute(id1, adj_mat);

	if (distance[id2] == 0)
		printf("There is no way to get from %s to %s\n", user1, user2);
	else
		printf("The distance between %s - %s is %d\n", user1,
			   user2, distance[id2]);
	
	free(distance);
}

void suggestions(char *input, int **adj_mat)
{
	// parse the input
	strtok(input, " ");
	char *user = strtok(NULL, "\n");
	int id = get_user_id(user);

	// compute the distance
	int *distance = distance_compute(id, adj_mat);

	int suggestions[MAX_USERS];
	int count = 0;

	// find the suggestions
	for (int i = 0; i < MAX_USERS; i++) {
		if (distance[i] == 2) {
			suggestions[count++] = i;
		}
	}

	// sort the suggestions
	for (int i = 0; i < count - 1; i++) {
		for (int j = 0; j < count - i - 1; j++)
			if (suggestions[j] > suggestions[j + 1]) {
				int temp = suggestions[j];
				suggestions[j] = suggestions[j + 1];
				suggestions[j + 1] = temp;
			}
	}

	if (count == 0) {
		printf("There are no suggestions for %s\n", user);
	} else {
		printf("Suggestions for %s:\n", user);
		for (int i = 0; i < count; i++)
			printf("%s\n", get_user_name(suggestions[i]));
	}

	free(distance);
}

void common_friends(char *input, int **adj_mat)
{
	// parse the input
	strtok(input, " ");
	char *user1 = strtok(NULL, " ");
	char *user2 = strtok(NULL, "\n");

	// get the user ids
	int id1 = get_user_id(user1);
	int id2 = get_user_id(user2);

	int common_friends[MAX_USERS];
	int count = 0;

	// find the common friends
	for (int i = 0; i < MAX_USERS; i++) {
		if (adj_mat[id1][i] && adj_mat[id2][i])
			common_friends[count++] = i;
	}

	if (count == 0) {
		printf("No common friends for %s and %s\n", user1, user2);
	} else {
		printf("The common friends between %s and %s are:\n", user1, user2);
		for (int i = 0; i < count; i++)
			printf("%s\n", get_user_name(common_friends[i]));
	}
}

void number_friends(char *input, int *no_friends)
{
	// parse the input
	strtok(input, " ");
	char *user = strtok(NULL, "\n");

	// get the user id
	int id = get_user_id(user);

	// print the number of friends
	printf("%s has %d friends\n", user, no_friends[id]);
}

void popular_friends(char *input, int **adj_mat, int *no_friends)
{
	// parse the input
	strtok(input, " ");
	char *user = strtok(NULL, "\n");

	// get the user id
	int id = get_user_id(user);

	// find the most popular friend
	int max_friends = no_friends[id];
	int max_id = id;

	// iterate over the friends
	for (int i = 0; i < MAX_USERS; i++) {
		if (adj_mat[id][i] == 1) {
			if (no_friends[i] > max_friends) {
				max_friends = no_friends[i];
				max_id = i;
			}
		}
	}

	if (max_friends == no_friends[id])
		printf("%s is the most popular\n", user);
	else
		printf("%s is the most popular friend of %s\n",
			   get_user_name(max_id), user);
}
