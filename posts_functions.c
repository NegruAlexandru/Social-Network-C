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
	strtok(input, " ");
	char *user = strtok(NULL, " ");
	char *title = strtok(NULL, "\"");
	printf("title: %s\n", title);
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

// might be wrong
void common_repost(char *input, post_t **posts, unsigned int *post_counter)
{
	input[strlen(input) - 1] = '\0';

	char *tmp = strtok(NULL, " ");
	char *post_id1 = strtok(NULL, " ");
	char *post_id2 = strtok(NULL, "\n");

	int post_id1_int = atoi(post_id1);
	int post_id2_int = atoi(post_id2);

	g_node_t *root1 = posts[post_id1_int]->events->root;
	g_node_t *root2 = posts[post_id2_int]->events->root;

	g_node_t **queue1 = calloc(4000, sizeof(g_node_t *));
	g_node_t **queue2 = calloc(4000, sizeof(g_node_t *));
	int visited1[4000] = {0};
	int visited2[4000] = {0};
	int front1 = 0, rear1 = 0;
	int front2 = 0, rear2 = 0;
	queue1[rear1++] = root1;
	queue2[rear2++] = root2;

	int common_repost = 0;

	while (front1 < rear1 && front2 < rear2) {
		g_node_t *node1 = queue1[front1++];
		g_node_t *node2 = queue2[front2++];

		visited1[((post_t *)node1->data)->id] = 1;
		visited2[((post_t *)node2->data)->id] = 1;

		if (((post_t *)node1->data)->id == ((post_t *)node2->data)->id) {
			common_repost = ((post_t *)node1->data)->id;
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

	if (common_repost)
		printf("Common repost: %d\n", common_repost);
	else
		printf("No common repost");
}