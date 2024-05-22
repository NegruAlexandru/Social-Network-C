#include "feed_functions.h"
#include "feed.h"
#include "posts.h"
#include "users.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void feed(char *input, int **adj_mat, post_array_t *posts)
{
	strtok(input, " ");
	char *user = strtok(NULL, " ");
	char *feed_size = strtok(NULL, "\n");

	int feed_size_int = atoi(feed_size);
	int user_id = get_user_id(user);
	int count = 0;
	int *friends = adj_mat[user_id];

	for (int i = posts->size - 1; i >= 0 && count < feed_size_int; i--) {
		if (posts->array[i]->user_id == user_id) {
			if (posts->array[i]->title) {
				printf("%s: \"%s\"\n", get_user_name(posts->array[i]->user_id), posts->array[i]->title);
				count++;
			}
		} else {
			for (int j = 0; j < 518; j++) {
				if (friends[j] == 1 && posts->array[i]->user_id == j && posts->array[i]->title) {
					printf("%s: \"%s\"\n", get_user_name(posts->array[i]->user_id), posts->array[i]->title);
					count++;
					break;
				}
			}
		}
	}
}

void view_profile(char *input, post_array_t *posts)
{
	strtok(input, " ");
	char *user = strtok(NULL, "\n");

	int user_id = get_user_id(user);
	for (unsigned int i = 0; i < posts->size; i++) {
		if (posts->array[i]->user_id == user_id) {
			if (posts->array[i]->title) {
				printf("Posted: \"%s\"\n", posts->array[i]->title);
			} else {
				printf("Reposted: \"%s\"\n", posts->array[posts->array[i]->parent_post_id - 1]->title);
			}
		}
	}
}

void friends_repost(char *input, int **adj_mat, post_array_t *posts)
{
    strtok(input, " ");
    char *user = strtok(NULL, " ");
    char *post_id = strtok(NULL, "\n");

    int user_id = get_user_id(user);
    int post_id_int = atoi(post_id);

    for(unsigned int i = 0; i < posts->size; i++) {
        if(posts->array[i]->parent_post_id == post_id_int) {
            for(int j = 0; j < 518; j++) {
                if(adj_mat[user_id][j] == 1 && posts->array[i]->user_id == j) {
                    printf("%s\n", get_user_name(j));
                }
            }
        }
    }
}

void common_groups(char *input, int **adj_mat)
{
    strtok(input, " ");
    char *user = strtok(NULL, "\n");

    int user_id = get_user_id(user);

    printf("The closest friend group of %s is:\n", user);

    // clique is a group of friends that are all friends with each other

    
}
