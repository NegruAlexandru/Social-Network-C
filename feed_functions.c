#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "feed_functions.h"
#include "users.h"
#include "feed.h"
#include "posts.h"


/* feed <nume> <feed-size>

Afișează cele mai recente <feed-size> postări ale unui utilizator și ale prietenilor lui. */
void feed(char *input, int **adj_mat, post_array_t *posts)
{
    (void)input;
    (void)adj_mat;
    (void)posts;
    // strtok(input, " ");
    // char *user = strtok(NULL, " ");
    // char *feed_size = strtok(NULL, "\n");

    // int feed_size_int = atoi(feed_size);
    // int user_id = get_user_id(user);

    // int *friends = adj_mat[user_id];
    // int *ids_of_friends_posts = calloc(feed_size_int, sizeof(int));
    // int count = 0;

    // // for(int i = 0; i<518 && count < feed_size_int; i++)
    // // {
    // //     if(friends[i] == 1)
    // //     {
    // //         for(unsigned int j = 0; j<posts->size; j++)
    // //         {
    // //             if(posts->array[j]->user_id == i && posts->array[j]->title)
    // //             {
    // //                 ids_of_friends_posts[count++] = j + 1;
    // //             }
    // //         }
    // //     }
    // // }
    
    // // for(int i = 0; i<518; i++)
    // // {
    // //     for(int j = i+1; j<518; j++)
    // //     {
    // //         if(ids_of_friends_posts[i] < ids_of_friends_posts[j])
    // //         {
    // //             int aux = ids_of_friends_posts[i];
    // //             ids_of_friends_posts[i] = ids_of_friends_posts[j];
    // //             ids_of_friends_posts[j] = aux;
    // //         }
    // //     }
    // // }
    // // for(int i = 0; i<feed_size_int; i++)
    // // {
    // //     // if(ids_of_friends_posts[i] != 0)
    // //     // {
    // //     //     printf("%s\n", posts->array[ids_of_friends_posts[i] - 1]->title);
    // //     // }
    // //     printf("%d\n", ids_of_friends_posts[i]);
    // // }
    // // free(ids_of_friends_posts);

    // for(unsigned int i = posts->size - 1; i >= 0; i--)
    // {
    //     if(posts->array[i]->user_id == user_id)
    //     {
    //         if(posts->array[i]->title)
    //         {
    //             printf("%s\n", posts->array[i]->title);
    //         }
    //     }
    //     else
    //     {
    //         for(int j = 0; j<518; j++)
    //         {
    //             if(friends[j] == 1 && posts->array[i]->user_id == j)
    //             {
    //                 printf("%s\n", posts->array[i]->title);
    //                 break;
    //             }
    //         }
    //     }
    // }
}

void view_profile(char *input, post_array_t *posts)
{
    strtok(input, " ");
    char *user = strtok(NULL, "\n");

    int user_id = get_user_id(user);
    for (unsigned int i = 0; i < posts->size; i++)
    {
        if (posts->array[i]->user_id == user_id)
        {
            if (posts->array[i]->title) {
                printf("Posted: \"%s\"\n", posts->array[i]->title);
            } else {
                printf("Reposted: \"%s\"\n", posts->array[posts->array[i]->parent_post_id - 1]->title);
            }
        }
    }
}

void friends_repost(char *input)
{
    (void)input;
}

void common_groups(char *input)
{
    (void)input;
}
