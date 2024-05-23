#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "posts.h"
#include "posts_functions.h"
#include "users.h"

void free_node(g_node_t *node)
{
	if (!node)
		return;

	for (int i = 0; i < node->n_children; i++)
		free_node(node->children[i]);

	free(node->children);

	free(node);
}

void free_posts(post_array_t *posts)
{
	for (unsigned int i = 0; i < posts->size; i++) {
		if (posts->array[i]) {
			if (posts->array[i]->title)
				free(posts->array[i]->title);

			if (posts->array[i]->events) {
				free_node(posts->array[i]->events->root);
				free(posts->array[i]->events);
			}

			free(posts->array[i]);
		}
	}

	free(posts->array);

	free(posts);
}

void handle_input_posts(char *input, post_array_t *posts)
{
	char *commands = strdup(input);
	char *cmd = strtok(commands, "\n ");

	if (!cmd)
		return;

	if (!strcmp(cmd, "create"))
		create_post(input, posts);
	else if (!strcmp(cmd, "repost"))
		create_repost(input, posts);
	else if (!strcmp(cmd, "common-repost"))
		common_repost(input, posts);
	else if (!strcmp(cmd, "like"))
		like_post(input, posts);
	else if (!strcmp(cmd, "ratio"))
		ratio_post(input, posts);
	else if (!strcmp(cmd, "delete"))
		delete_post(input, posts);
	else if (!strcmp(cmd, "get-likes"))
		get_likes(input, posts);
	else if (!strcmp(cmd, "get-reposts"))
		get_reposts(input, posts);

	free(commands);
}
