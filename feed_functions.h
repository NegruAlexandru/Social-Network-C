#include "posts.h"
#include "users.h"
#ifndef FEED_FUNCTIONS_H
#define FEED_FUNCTIONS_H

void feed(char *input, int **adj_mat, post_array_t *posts);
void view_profile(char *input, post_array_t *posts);
void friends_repost(char *input, int **adj_mat, post_array_t *posts);
void common_groups(char *input, int **adj_mat);

#endif