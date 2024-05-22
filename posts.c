#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "posts.h"
#include "posts_functions.h"
#include "users.h"

// free the memory allocated for the posts and the struct used to store them
void free_node(g_node_t *node)
{
	if (!node)
		return;

	// Free children nodes recursively
	for (int i = 0; i < node->n_children; i++)
		free_node(node->children[i]);

	// Free the node's children array
	free(node->children);

	// Free the node itself
	free(node);
}

// Function to free the entire posts array
void free_posts(post_array_t *posts)
{
	for (unsigned int i = 0; i < posts->size; i++) {
		if (posts->array[i]) {
			// Free the post's title
			free(posts->array[i]->title);

			// Free the event tree if it exists
			if (posts->array[i]->events) {
				// Free the root node (which recursively frees the entire tree)
				free_node(posts->array[i]->events->root);

				// Free the events structure
				free(posts->array[i]->events);
			}

			// Free the post structure
			free(posts->array[i]);
		}
	}

	// Free the posts array itself
	free(posts->array);

	// Free the posts structure
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
