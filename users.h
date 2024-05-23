#include <stdint.h>
#define MAX_USERS 518
#define INITIAL_NUM_POSTS 100

/**
 * Initializes the user list
*/
void init_users(void);

/**
 * Find the user_id of a user by it's name
 *
 * @param name - The name of the user
 * @return the id of the user, of -1 if name is not found
*/
uint16_t get_user_id(char *name);

/**
 * Find the user_id of a user by it's name
 *
 * @param id - The id of a user
 * @return the name of a user, of NULL if not found
*/
char *get_user_name(uint16_t id);

/**
 * Frees the memory allocated for the users
*/
void free_users(void);
