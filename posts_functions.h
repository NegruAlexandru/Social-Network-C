//
// Created by Alex on 20/05/2024.
//

#ifndef POSTS_FUNCTIONS_H
#define POSTS_FUNCTIONS_H

void create_post(char *input, post_array_t *posts);
void create_repost(char *input, post_array_t *posts);
void common_repost(g_node_t *root, int id1, int id2);
void like_post(char *input, post_array_t *posts);
void ratio_post(char *input, post_array_t *posts);
void delete_post(char *input, post_array_t *posts);
void get_likes(char *input, post_array_t *posts);
void print_reposts(g_node_t *root, int post_id);
void get_reposts(char *input, post_array_t *posts);

#endif
