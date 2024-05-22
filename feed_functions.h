#include "posts.h"
#ifndef FEED_FUNCTIONS_H
#define FEED_FUNCTIONS_H

void feed(char *input, int **adj_mat, post_array_t *posts);
void view_profile(char *input);
void friends_repost(char *input);
void common_groups(char *input);

#endif