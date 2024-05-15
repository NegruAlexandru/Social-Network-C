//
// Created by Alex on 14/05/2024.
//

#ifndef FRIENDS_FUNCTIONS_H
#define FRIENDS_FUNCTIONS_H

void add_friend(char *input, int **mtx, int *no_friends);
void remove_friend(char *input, int **mtx, int *no_friends);
void distance_between_friends(char *input, int **mtx);
void suggestions(char *input, int **mtx);
void common_friends(char *input, int **mtx);
void number_friends(char *input, int *no_friends);
void popular_friends(char *input, int **mtx, int *no_friends);

#endif
