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
	post->events->root->children = calloc(1, sizeof(g_node_t *));
	post->events->root->n_children = 0;

	posts->array[posts->index] = post;
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
		g_node_t *root = posts->array[post_id_int]->events->root;

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
		g_node_t *root = posts->array[post_id_int]->events->root;
		root->children[root->n_children] = node;
		root->n_children++;

		posts->index++;
	}
	printf("Created repost #%d for %s\n", posts->index - 1, user);
}

// might be wrong
void common_repost(char *input, post_array_t *posts)
{
	strtok(input, " ");
	char *post_id1 = strtok(NULL, " ");
	char *post_id2 = strtok(NULL, " ");

	int post_id1_int = atoi(post_id1);
	int post_id2_int = atoi(post_id2);

	g_node_t *root1 = posts->array[post_id1_int]->events->root;
	g_node_t *root2 = posts->array[post_id2_int]->events->root;

	g_node_t **queue1 = calloc(4000, sizeof(g_node_t *));
	g_node_t **queue2 = calloc(4000, sizeof(g_node_t *));
	int visited1[4000] = {0};
	int visited2[4000] = {0};
	int front1 = 0, rear1 = 0, front2 = 0, rear2 = 0;
	queue1[rear1++] = root1;
	queue2[rear2++] = root2;

	while (front1 < rear1 && front2 < rear2) {
		g_node_t *node1 = queue1[front1++];
		g_node_t *node2 = queue2[front2++];

		visited1[((post_t *)node1->data)->id] = 1;
		visited2[((post_t *)node2->data)->id] = 1;

		if (((post_t *)node1->data)->id == post_id2_int) {
			printf("Common repost: %d\n", ((post_t *)node1->data)->id);
			break;
		}

		if (((post_t *)node2->data)->id == post_id1_int) {
			printf("Common repost: %d\n", ((post_t *)node2->data)->id);
			break;
		}

		for (int i = 0; i < node1->n_children; i++) {
			if (!visited1[((post_t *)node1->children[i]->data)->id])
				queue1[rear1++] = node1->children[i];
		}

		for (int i = 0; i < node2->n_children; i++) {
			if (!visited2[((post_t *)node2->children[i]->data)->id])
				queue2[rear2++] = node2->children[i];
		}
	}
	printf("Common repost: -1");
}

void like_post(char *input, post_array_t *posts)
{
	strtok(input, " ");
	char *user = strtok(NULL, " ");
	char *post_id = strtok(NULL, " ");

	int user_id = get_user_id(user);
	int post_id_int = atoi(post_id);

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