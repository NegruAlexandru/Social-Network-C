#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "friends.h"
#include "users.h"
#include "friends_functions.h"

void handle_input_friends(char *input, int **mtx, int *no_friends)
{
	char *commands = strdup(input);
	char *cmd = strtok(commands, "\n ");

	if (!cmd)
		return;

	if (!strcmp(cmd, "add"))
		add_friend(input, mtx, no_friends);
	else if (!strcmp(cmd, "remove"))
		remove_friend(input, mtx, no_friends);
	else if (!strcmp(cmd, "suggestions"))
		suggestions(input, mtx);
	else if (!strcmp(cmd, "distance"))
		distance_between_friends(input, mtx);
	else if (!strcmp(cmd, "common"))
		common_friends(input, mtx);
	else if (!strcmp(cmd, "friends"))
		number_friends(input, no_friends);
	else if (!strcmp(cmd, "popular"))
		popular_friends(input, mtx, no_friends);
	// TODO: Add function
	free(commands);
}
