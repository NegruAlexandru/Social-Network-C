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
		post_t **tmp = realloc(posts->array, posts->capacity *
							   sizeof(post_t *));

		if (!tmp) {
			printf("Error reallocating memory");
			return;
		}

		posts->array = tmp;
	}

	post_t *post = calloc(1, sizeof(post_t));
	post->id = posts->size + 1;
	post->user_id = user_id;
	post->title = strdup(title);
	post->like_count = 0;
	post->events = calloc(1, sizeof(g_tree_t));
	post->events->root = calloc(1, sizeof(g_node_t));
	post->events->root->data = post;
	post->events->root->children = calloc(100, sizeof(g_node_t *));
	post->events->root->n_children = 0;

	posts->array[posts->size] = post;
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
	post_id_int--;
	if (repost_id) {
		// repost la repost
		int repost_id_int = atoi(repost_id);

		// Create repost
		post_t *repost = calloc(1, sizeof(post_t));
		repost->id = posts->size + 1;
		repost->user_id = user_id;
		repost->title = NULL;
		repost->like_count = 0;
		repost->events = NULL;

		// Create repost node
		g_node_t *repost_node = calloc(1, sizeof(g_node_t));
		repost_node->data = repost;
		repost_node->children = calloc(100, sizeof(g_node_t *));
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

		posts->array[posts->size] = repost;
		posts->size++;
		free(queue);
	} else {
		// repost la post
		post_t *repost = calloc(1, sizeof(post_t));
		repost->id = posts->size + 1;
		repost->user_id = user_id;
		repost->title = NULL;
		repost->like_count = 0;
		repost->events = NULL;

		g_node_t *node = calloc(1, sizeof(g_node_t));
		node->data = repost;
		node->children = calloc(100, sizeof(g_node_t *));
		node->n_children = 0;

		int n_children = posts->array[post_id_int]->events->root->n_children;
		posts->array[post_id_int]->events->root->children[n_children] = node;
		posts->array[post_id_int]->events->root->n_children++;

		posts->array[posts->size] = repost;
		posts->size++;
	}

	printf("Created repost #%d for %s\n", posts->size, user);
}

g_node_t *find_lca(g_node_t *root, int repost_id_1, int repost_id_2)
{
	if (!root)
		return NULL;

	if (((post_t *)root->data)->id == repost_id_1 ||
		((post_t *)root->data)->id == repost_id_2)
		return root;

	int count = 0;
	g_node_t *temp = NULL;
	g_node_t *lca = NULL;

	for (int i = 0; i < root->n_children; i++) {
		temp = find_lca(root->children[i], repost_id_1, repost_id_2);
		if (temp) {
			count++;
			lca = temp;
		}
	}

	if (count == 2)
		return root;

	return lca;
}

// Implementation of common_repost function
void common_repost(char *input, post_array_t *posts)
{
	strtok(input, " ");
	char *post_id = strtok(NULL, " ");
	char *repost_id_1 = strtok(NULL, " ");
	char *repost_id_2 = strtok(NULL, " ");

	int post_id_int = atoi(post_id);
	int repost_id_1_int = atoi(repost_id_1);
	int repost_id_2_int = atoi(repost_id_2);
	post_id_int--;

	g_node_t *root = posts->array[post_id_int]->events->root;

	g_node_t **queue = calloc(4000, sizeof(g_node_t *));
	int visited[4000] = {0};
	int front = 0, rear = 0;
	queue[rear++] = root;

	g_node_t *lca = NULL;

	while (front < rear) {
		g_node_t *node = queue[front++];
		visited[((post_t *)node->data)->id] = 1;

		if (((post_t *)node->data)->id == repost_id_1_int ||
			((post_t *)node->data)->id == repost_id_2_int) {
			lca = find_lca(root, repost_id_1_int, repost_id_2_int);
			break;
		}

		for (int i = 0; i < node->n_children; i++) {
			if (!visited[((post_t *)node->children[i]->data)->id])
				queue[rear++] = node->children[i];
		}
	}

	printf("The first common repost of %d and %d is %d\n",
		   repost_id_1_int, repost_id_2_int, ((post_t *)lca->data)->id);

	free(queue);
}

void like_post(char *input, post_array_t *posts)
{
	strtok(input, " ");
	char *user = strtok(NULL, " ");
	char *post_id = strtok(NULL, " ");
	char *repost_id = strtok(NULL, " ");

	int user_id = get_user_id(user);
	int post_id_int = atoi(post_id);
	post_id_int--;

	if (!repost_id) {
		if (!posts->array[post_id_int]->likes[user_id]) {
			posts->array[post_id_int]->likes[user_id] = true;
			posts->array[post_id_int]->like_count++;
			printf("User %s liked post \"%s\"\n",
				   user, posts->array[post_id_int]->title);
		} else {
			printf("User %s unliked post \"%s\"\n",
				   user, posts->array[post_id_int]->title);
			posts->array[post_id_int]->likes[user_id] = false;
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
				if (!((post_t *)node->data)->likes[user_id]) {
					((post_t *)node->data)->likes[user_id] = true;
					((post_t *)node->data)->like_count++;
					printf("User %s liked repost \"%s\"\n",
						   user, posts->array[post_id_int]->title);
				} else {
					printf("User %s unliked repost \"%s\"\n",
						   user, posts->array[post_id_int]->title);
					((post_t *)node->data)->likes[user_id] = false;
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
	strtok(input, " ");
	char *post_id = strtok(NULL, " ");
	int post_id_int = atoi(post_id);
	post_id_int--;

	post_t *original_post = posts->array[post_id_int];
	int original_like_count = original_post->like_count;

	g_node_t *root = original_post->events->root;
	g_node_t **queue = calloc(4000, sizeof(g_node_t *));
	int visited[4000] = {0};
	int front = 0, rear = 0;
	queue[rear++] = root;

	int max_likes = -1;
	int max_likes_repost_id = -1;

	while (front < rear) {
		g_node_t *node = queue[front++];
		visited[((post_t *)node->data)->id] = 1;

		post_t *repost = (post_t *)node->data;
		if (repost->id != original_post->id &&
			repost->like_count > original_like_count) {
			if (repost->like_count > max_likes ||
				(repost->like_count == max_likes &&
				repost->id < max_likes_repost_id)) {
				max_likes = repost->like_count;
				max_likes_repost_id = repost->id;
			}
		}

		for (int i = 0; i < node->n_children; i++)
			if (!visited[((post_t *)node->children[i]->data)->id])
				queue[rear++] = node->children[i];
	}

	free(queue);

	if (max_likes_repost_id == -1)
		printf("The original post is the highest rated\n");
	else
		printf("Post %d got ratio'd by repost %d\n",
			   original_post->id, max_likes_repost_id);
}

void free_repost(post_array_t *posts, g_node_t **root)
{
	if (!*root)
		return;

<<<<<<< HEAD
	for (int i = 0; i < root->n_children; i++)
		if (root->children[i])
			free_repost(root->children[i]);
=======
	for (int i = 0; i < (*root)->n_children; i++)
		if ((*root)->children[i])
			free_repost(posts, &(*root)->children[i]);
>>>>>>> dea4dea (fixed memory leaks)

	free((*root)->children);
	posts->array[((post_t *)(*root)->data)->id - 1] = NULL;
	free((*root)->data);
	free(*root);

	*root = NULL;
}

void free_post(post_array_t *posts, post_t *post)
{
	free(post->title);
	free_repost(posts, &post->events->root);
	free(post->events);
	free(post);
}

void delete_post(char *input, post_array_t *posts)
{
	strtok(input, " ");
	char *post_id = strtok(NULL, " ");
	char *repost_id = strtok(NULL, " ");
	int post_id_int = atoi(post_id);
	post_id_int--;

<<<<<<< HEAD
	if (!repost_id) {
		free(posts->array[post_id_int]->title);
		free(posts->array[post_id_int]->events->root->children);
		free(posts->array[post_id_int]->events->root);
		free(posts->array[post_id_int]->events);
		free(posts->array[post_id_int]);
=======
	if(!repost_id){
		free_post(posts, posts->array[post_id_int]);
>>>>>>> dea4dea (fixed memory leaks)
		posts->array[post_id_int] = NULL;
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
<<<<<<< HEAD
				printf("Deleted repost #%d of post \"%s\"\n",
					   repost_id_int, posts->array[post_id_int]->title);
				free_repost(node);
=======
				printf("Deleted repost #%d of post \"%s\"\n", repost_id_int, posts->array[post_id_int]->title);
				free_repost(posts, &node);
				posts->array[repost_id_int - 1] = NULL;
				posts->array[post_id_int]->events->root->n_children--;
				posts->array[post_id_int]->events->root->children[posts->array[post_id_int]->events->root->n_children] = NULL;
>>>>>>> dea4dea (fixed memory leaks)
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

void get_likes(char *input, post_array_t *posts)
{
	strtok(input, " ");
	char *post_id = strtok(NULL, " ");
	char *repost_id = strtok(NULL, " ");

	int post_id_int = atoi(post_id);
	post_id_int--;
	if (!repost_id) {
		printf("Post \"%s\" has %d likes\n", posts->array[post_id_int]->title,
			   posts->array[post_id_int]->like_count);
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
				printf("Repost #%d has %d likes\n",
					   repost_id_int, ((post_t *)node->data)->like_count);
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

void print_reposts(g_node_t *root, int post_id)
{
	if (!root)
		return;
	int user_id = ((post_t *)root->data)->user_id;
	if (((post_t *)root->data)->id != post_id + 1)
		printf("Repost #%d by %s\n",
			   ((post_t *)root->data)->id,
			   get_user_name(user_id)); // "Repost #%d by %s\n

	for (int i = 0; i < root->n_children; i++)
		print_reposts(root->children[i], post_id);
}

void get_reposts(char *input, post_array_t *posts)
{
	strtok(input, " ");
	char *post_id = strtok(NULL, " ");
	char *repost_id = strtok(NULL, " ");

	int post_id_int = atoi(post_id);
	post_id_int--;

	if (!repost_id) {
		printf("\"%s\" - Post by %s\n",
			   posts->array[post_id_int]->title,
			   get_user_name(posts->array[post_id_int]->user_id));
		print_reposts(posts->array[post_id_int]->events->root, post_id_int);
	} else {
		// find the node with the repost_id and then use print_reposts
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
		free(queue);
	}
}
