#include <stdbool.h>
#include "users.h"

#ifndef POSTS_H
#define POSTS_H

typedef struct g_node_t g_node_t;
struct g_node_t
{
	void *data;
	g_node_t **children;
	int n_children;
};

typedef struct g_tree_t g_tree_t;
struct g_tree_t
{
	g_node_t *root;
};

typedef struct post_t post_t;
struct post_t {
	int id;
	char *title;
	int parent_post_id;
	int user_id;
	int like_count;
	bool likes[MAX_USERS];
	g_tree_t *events;
};

typedef struct post_array_t post_array_t;
struct post_array_t {
	post_t **array;
	unsigned int size;
	unsigned int capacity;
};

/**
 * Function that handles the calling of every command from task 2
*/
void handle_input_posts(char *input, post_array_t *posts);

#endif // POSTS_H
