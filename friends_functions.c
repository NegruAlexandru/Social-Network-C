//
// Created by Alex on 14/05/2024.
//

#include "friends_functions.h"
#include "users.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void add_friend(char *input, int **mtx, int *no_friends)

{
	strtok(input, " ");
	char *user1 = strtok(NULL, " ");
	char *user2 = strtok(NULL, "\n");
	int id1 = get_user_id(user1);
	int id2 = get_user_id(user2);

	mtx[id1][id2] = 1;
	mtx[id2][id1] = 1;

	no_friends[id1]++;
	no_friends[id2]++;

	printf("Added connection %s - %s\n", user1, user2);
}

void remove_friend(char *input, int **mtx, int *no_friends)
{
	strtok(input, " ");
	char *user1 = strtok(NULL, " ");
	char *user2 = strtok(NULL, "\n");

	int id1 = (int)get_user_id(user1);
	int id2 = (int)get_user_id(user2);

	mtx[id1][id2] = 0;
	mtx[id2][id1] = 0;

	no_friends[id1]--;
	no_friends[id2]--;

	printf("Removed connection %s - %s\n", user1, user2);
}

void distance_between_friends(char *input, int **mtx)
{
	strtok(input, " ");
	char *user1 = strtok(NULL, " ");
	char *user2 = strtok(NULL, "\n");

	int id1 = get_user_id(user1);
	int id2 = get_user_id(user2);

	int *visited = calloc(518, sizeof(int));
	int *distance = calloc(518, sizeof(int));

	int *queue = calloc(518, sizeof(int));
	int front = 0, rear = 0;

	queue[rear++] = id1;
	visited[id1] = 1;

	while (front < rear) {
		int node = queue[front++];
		for (int i = 0; i < 518; i++) {
			if (mtx[node][i] && !visited[i]) {
				queue[rear++] = i;
				visited[i] = 1;
				distance[i] = distance[node] + 1;
			}
		}
	}
	if(distance[id2] == 0)
		printf("There is no way to get from %s to %s\n", user1, user2);
	else
		printf("The distance between %s - %s is %d\n", user1, user2, distance[id2]);

	free(visited);
	free(queue);
	free(distance);
}

void suggestions(char *input, int **mtx)
{
	strtok(input, " ");
	char *user = strtok(NULL, "\n");
	int id = get_user_id(user);

	int *visited = calloc(518, sizeof(int));
	int *distance = calloc(518, sizeof(int));

	int *queue = calloc(518, sizeof(int));
	int front = 0, rear = 0;

	queue[rear++] = id;
	visited[id] = 1;

	while (front < rear) {
		int node = queue[front++];
		for (int i = 0; i < 518; i++) {
			if (mtx[node][i] && !visited[i]) {
				queue[rear++] = i;
				visited[i] = 1;
				distance[i] = distance[node] + 1;
			}
		}
	}

	int suggestions[10];
	int count = 0;

	for (int i = 0; i < 518; i++) {
		if (distance[i] == 2) {
			suggestions[count++] = i;
		}
	}
	for (int i = 0; i < count - 1; i++) {
		for (int j = 0; j < count - i - 1; j++)
			if (suggestions[j] > suggestions[j + 1]) {
				int temp = suggestions[j];
				suggestions[j] = suggestions[j + 1];
				suggestions[j + 1] = temp;
			}
	}

	printf("Suggestions for %s:\n", user);
	for (int i = 0; i < count; i++) {
		printf("%s\n", get_user_name(suggestions[i]));
	}

	free(visited);
	free(queue);
	free(distance);
}

void common_friends(char *input, int **mtx)
{
	strtok(input, " ");
	char *user1 = strtok(NULL, " ");
	char *user2 = strtok(NULL, "\n");

	int id1 = get_user_id(user1);
	int id2 = get_user_id(user2);

	int common_friends[518];
	int count = 0;

	for (int i = 0; i < 518; i++) {
		if (mtx[id1][i] && mtx[id2][i]) {
			common_friends[count++] = i;
		}
	}

	if(count == 0)
		printf("No common friends for %s and %s\n", user1, user2);
	else{
		printf("The common friends between %s and %s are:\n", user1, user2);
		for (int i = 0; i < count; i++) {
			printf("%s\n", get_user_name(common_friends[i]));
		}
	}
}

void number_friends(char *input, int *no_friends)
{
	strtok(input, " ");
	char *user = strtok(NULL, "\n");

	int id = get_user_id(user);

	printf("%s has %d friends\n", user, no_friends[id]);
}

void popular_friends(char *input, int **adj_mat, int *no_friends)
{
	strtok(input, " ");
	char *user = strtok(NULL, "\n");

	int id = get_user_id(user);
	int max_friends = no_friends[id];
	int max_id = id;
	for(int i = 0; i < 518; i++){
		if(adj_mat[id][i] == 1){
			if(no_friends[i] > max_friends){
				max_friends = no_friends[i];
				max_id = i;
			}
		}
	}
	if(max_friends == no_friends[id])
		printf("%s is the most popular\n", user);
	else
		printf("%s is the most popular friend of %s\n",
			   get_user_name(max_id), user);
}