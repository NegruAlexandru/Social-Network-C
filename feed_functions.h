#include "posts.h"
#include "users.h"
#ifndef FEED_FUNCTIONS_H
#define FEED_FUNCTIONS_H

/**
 * Function that creates a feed for a user
 *
 */
void feed(char *input, int **adj_mat, post_array_t *posts);
/**
 * Function that returns the profile of a user
 *
 */
void view_profile(char *input, post_array_t *posts);
/**
 * Function that returns the reposts of a user's friends
 *
 */
void friends_repost(char *input, int **adj_mat, post_array_t *posts);
/**
 * Function that returns the common group of a user
 *
 */
void common_groups(char *input, int **adj_mat);

#endif
