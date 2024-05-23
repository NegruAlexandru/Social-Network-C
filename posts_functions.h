#include "posts.h"

#ifndef POSTS_FUNCTIONS_H
#define POSTS_FUNCTIONS_H

#define MAX_CHILDREN 100
#define MAX_QUEUE_SIZE 100

/**
 * Function that handles the creation of a post
*/
void create_post(char *input, post_array_t *posts);
/**
 * Function that handles the creation of a repost
*/
void create_repost(char *input, post_array_t *posts);
/**
 * Function that returns the lowest common ancestor of two reposts
*/
void common_repost(char *input, post_array_t *posts);
/**
 * Function that handles the liking of a post
*/
void like_post(char *input, post_array_t *posts);
/**
 * Function that calculates the ratio of likes between a repost and its parent post
*/
void ratio_post(char *input, post_array_t *posts);
/**
 * Function that handles the deletion of a post
*/
void delete_post(char *input, post_array_t *posts);
/**
 * Function that returns the number of likes of a post
*/
void get_likes(char *input, post_array_t *posts);
/**
 * Function that prints the reposts of a post
*/
void print_reposts(g_node_t *root, int post_id);
/**
 * Function that returns the reposts of a post
*/
void get_reposts(char *input, post_array_t *posts);

#endif
