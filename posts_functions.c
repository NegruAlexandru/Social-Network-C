//
// Created by Alex on 20/05/2024.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "users.h"
#include "posts.h"
#include "posts_functions.h"

void create_post(char *input, post_array_t *posts)
{
	strtok(input, " ");
	char *user = strtok(NULL, " ");
	char *title = strtok(NULL, "\"");
	int user_id = get_user_id(user);

	if (posts->size == posts->capacity) {
		posts->capacity *= 2;
		post_t **tmp = realloc(posts->array, posts->capacity * sizeof(post_t *));

		if (!tmp) {
			printf("Error reallocating memory");
			return;
		}

		posts->array = tmp;
	}

	post_t *post = calloc(1, sizeof(post_t));
	post->id = posts->index;
	post->user_id = user_id;
	post->title = strdup(title);
	post->like_count = 0;
	post->events = calloc(1, sizeof(g_tree_t));
	post->events->root = calloc(1, sizeof(g_node_t));
	post->events->root->data = post;
	post->events->root->children = calloc(100, sizeof(g_node_t *));
	post->events->root->n_children = 0;

	posts->array[posts->index - 1] = post;
	posts->index++;
	posts->size++;

	printf("Created \"%s\" for %s\n", title, user);
}

void create_repost(char *input, post_array_t *posts)
{
	strtok(input, " ");
	char *user = strtok(NULL, " ");
	char *post_id = strtok(NULL, " ");
	char *repost_id = strtok(NULL, " ");

	int user_id = get_user_id(user);
	int post_id_int = atoi(post_id);

	if (repost_id) {
		// repost la repost
		int repost_id_int = atoi(repost_id);

		// Create repost
		post_t *repost = calloc(1, sizeof(post_t));
		repost->id = posts->index;
		repost->user_id = user_id;
		repost->title = NULL;
		repost->like_count = 0;
		repost->events = NULL;

		// Create repost node
		g_node_t *repost_node = calloc(1, sizeof(g_node_t));
		repost_node->data = repost;
		repost_node->children = calloc(1, sizeof(g_node_t *));
		repost_node->n_children = 0;

		// Tree root
		g_node_t *root;
		for (unsigned int i = 0; i < posts->size; i++) {
			if (posts->array[i]->id == post_id_int) {
				root = posts->array[i]->events->root;
				break;
			}
		}

		// Find repost_id node
		g_node_t *repost_id_node = NULL;

		g_node_t **queue = calloc(4000, sizeof(g_node_t *));
		int visited[4000] = {0};
		int front = 0, rear = 0;
		queue[rear++] = root;

		while (front < rear) {
			g_node_t *node = queue[front++];
			visited[((post_t *)node->data)->id] = 1;

			if (((post_t *)node->data)->id == repost_id_int) {
				repost_id_node = node;
				break;
			}

			for (int i = 0; i < node->n_children; i++) {
				if (!visited[((post_t *)node->children[i]->data)->id])
					queue[rear++] = node->children[i];
			}
		}

		// Add repost node to repost_id_node
		repost_id_node->children[repost_id_node->n_children] = repost_node;
		repost_id_node->n_children++;

		posts->index++;
	} else {
		// repost la post
		post_t *post = calloc(1, sizeof(post_t));
		post->id = posts->index;
		post->user_id = user_id;
		post->title = NULL;
		post->like_count = 0;
		post->events = NULL;

		g_node_t *node = calloc(1, sizeof(g_node_t));
		node->data = post;
		node->children = calloc(1, sizeof(g_node_t *));
		node->n_children = 0;

		for (unsigned int i = 0; i < posts->size; i++) {
			if (posts->array[i]->id == post_id_int) {
				posts->array[i]->events->root->children[posts->array[i]->events->root->n_children] = node;
				posts->array[i]->events->root->n_children++;
				break;
			}
		}

		posts->index++;
	}
	printf("Created repost #%d for %s\n", posts->index - 1, user);
}

void common_repost(char *input, post_array_t *posts)
{
	// bfs
}

void like_post(char *input, post_array_t *posts)
{
	strtok(input, " ");
	char *user = strtok(NULL, " ");
	char *post_id = strtok(NULL, " ");
	char *repost_id = strtok(NULL, " ");

	int user_id = get_user_id(user);
	int post_id_int = atoi(post_id);

	if(!repost_id) {
		if(!posts->array[post_id_int]->likes[user_id]) {
		posts->array[post_id_int]->likes[user_id] = calloc(1, sizeof(bool));
		*posts->array[post_id_int]->likes[user_id] = true;
		posts->array[post_id_int]->like_count++;
		printf("User %s liked post \"%s\"\n", user, posts->array[post_id_int]->title);
		} else {
			printf("User %s unliked post \"%s\"\n", user, posts->array[post_id_int]->title);
			free(posts->array[post_id_int]->likes[user_id]);
			posts->array[post_id_int]->likes[user_id] = NULL;
			posts->array[post_id_int]->like_count--;
		}
	} else {
		int repost_id_int = atoi(repost_id);
		g_node_t *root = posts->array[post_id_int]->events->root;

		g_node_t **queue = calloc(4000, sizeof(g_node_t *));
		int visited[4000] = {0};
		int front = 0, rear = 0;
		queue[rear++] = root;

		while (front < rear) {
			g_node_t *node = queue[front++];
			visited[((post_t *)node->data)->id] = 1;

			if (((post_t *)node->data)->id == repost_id_int) {
				if(!((post_t *)node->data)->likes[user_id]) {
					((post_t *)node->data)->likes[user_id] = calloc(1, sizeof(bool));
					*((post_t *)node->data)->likes[user_id] = true;
					((post_t *)node->data)->like_count++;
					printf("User %s liked repost \"%s\"\n", user, posts->array[post_id_int]->title);
				} else {
					printf("User %s unliked repost \"%s\"\n", user, posts->array[post_id_int]->title);
					free(((post_t *)node->data)->likes[user_id]);
					((post_t *)node->data)->likes[user_id] = NULL;
					((post_t *)node->data)->like_count--;
				}
				break;
			}

			for (int i = 0; i < node->n_children; i++) {
				if (!visited[((post_t *)node->children[i]->data)->id])
					queue[rear++] = node->children[i];
			}
		}
		free(queue);
	}
}
void ratio_post(char *input, post_array_t *posts)
{
	(void) input;
	(void) posts;
}
void delete_post(char *input, post_array_t *posts)
{
	(void) input;
	(void) posts;
}
void get_likes(char *input, post_array_t *posts)
{
	(void) input;
	(void) posts;
}

void print_reposts(g_node_t *root, int post_id)
{
	if (!root)
		return;

	if(((post_t *)root->data)->id != post_id)
		printf("Repost #%d by %s\n", ((post_t *)root->data)->id, get_user_name(((post_t *)root->data)->user_id)); // "Repost #%d by %s\n

	for (int i = 0; i < root->n_children; i++)
		print_reposts(root->children[i], post_id);
}

void get_reposts(char *input, post_array_t *posts)
{
	strtok(input, " ");
	char *post_id = strtok(NULL, " ");
	char *repost_id = strtok(NULL, " ");

	int post_id_int = atoi(post_id);

	for (unsigned int i = 0; i < posts->size; i++) {
		if (posts->array[i]->id == post_id_int) {
			post_id_int = i;
			break;
		}
	}

	if(!repost_id) {
		printf("\"%s\" - Post by %s\n", posts->array[post_id_int]->title, get_user_name(posts->array[post_id_int]->user_id));
		print_reposts(posts->array[post_id_int]->events->root, post_id_int);
	} else {
		//find the node with the repost_id and then use print_reposts
		int repost_id_int = atoi(repost_id);
		g_node_t *root = posts->array[post_id_int]->events->root;

		g_node_t **queue = calloc(4000, sizeof(g_node_t *));
		int visited[4000] = {0};
		int front = 0, rear = 0;
		queue[rear++] = root;

		while (front < rear) {
			g_node_t *node = queue[front++];
			visited[((post_t *)node->data)->id] = 1;

			if (((post_t *)node->data)->id == repost_id_int) {
				print_reposts(node, post_id_int);
				break;
			}

			for (int i = 0; i < node->n_children; i++) {
				if (!visited[((post_t *)node->children[i]->data)->id])
					queue[rear++] = node->children[i];
			}
		}
	}
}