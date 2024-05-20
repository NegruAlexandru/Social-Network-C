//
// Created by Alex on 20/05/2024.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "users.h"
#include "posts.h"
#include "posts_functions.h"

void create_post(char *input, post_t **posts, unsigned int *post_counter)
{
	char *tmp = strtok(NULL, " ");
	char *title = strtok(NULL, " ");
	char *user = strtok(NULL, "\n");
	int user_id = get_user_id(user);

	post_t *post = calloc(1, sizeof(post_t));
	post->id = *post_counter;
	post->user_id = user_id;
	post->title = strdup(title);
	post->like_count = 0;
	post->events = calloc(1, sizeof(g_tree_t));
	post->events->root = calloc(1, sizeof(g_node_t));
	post->events->root->data = post;
	post->events->root->children = calloc(1, sizeof(g_node_t *));
	post->events->root->n_children = 0;

	posts[*post_counter] = post;
	(*post_counter)++;

	printf("Created \"%s\" for %s", title, user);
}

void create_repost(char *input, post_t **posts, unsigned int *post_counter)
{
	input[strlen(input) - 1] = '\0';

	char *tmp = strtok(NULL, " ");
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
		repost->id = *post_counter;
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
		g_node_t *root = posts[post_id_int]->events->root;

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

		(*post_counter)++;
	} else {
		// repost la post
		post_t *post = calloc(1, sizeof(post_t));
		post->id = *post_counter;
		post->user_id = user_id;
		post->title = NULL;
		post->like_count = 0;
		post->events = NULL;

		g_node_t *node = calloc(1, sizeof(g_node_t));
		node->data = post;
		node->children = calloc(1, sizeof(g_node_t *));
		node->n_children = 0;

		g_node_t *root = posts[post_id_int]->events->root;
		root->children[root->n_children] = node;

		(*post_counter)++;
	}
	printf("Create repost#%d for %s", *post_counter - 1, user);
}
