//
// Created by Alex on 20/05/2024.
//

#ifndef POSTS_FUNCTIONS_H
#define POSTS_FUNCTIONS_H

void create_post(char *input, post_t **posts, unsigned int *post_counter);
void create_repost(char *input, post_t **posts, unsigned int *post_counter);
void common_repost(char *input, post_t **posts, unsigned int *post_counter);
void like_post(char *input, post_t **posts, unsigned int *post_counter);
void ratio_post(char *input, post_t **posts, unsigned int *post_counter);
void delete_post(char *input, post_t **posts, unsigned int *post_counter);
void get_likes(char *input, post_t **posts, unsigned int *post_counter);
void get_reposts(char *input, post_t **posts, unsigned int *post_counter);

#endif
