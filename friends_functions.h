#ifndef FRIENDS_FUNCTIONS_H
#define FRIENDS_FUNCTIONS_H

/*
 * Function that handles adding a friend connection
 */
void add_friend(char *input, int **adj_mat, int *no_friends);
/*
 * Function that handles removing a friend connection
 */
void remove_friend(char *input, int **adj_mat, int *no_friends);
/*
 * Function that returns the distance between two users
 */
void distance_between_friends(char *input, int **adj_mat);
/*
 * Function that returns friend suggestions for a user
 */
void suggestions(char *input, int **adj_mat);
/*
 * Function that returns the common friends of two users
 */
void common_friends(char *input, int **adj_mat);
/*
 * Function that returns the number of friends of a user
 */
void number_friends(char *input, int *no_friends);
/*
 * Function that returns the most popular friend of a user (can be itself)
 */
void popular_friends(char *input, int **adj_mat, int *no_friends);

#endif
