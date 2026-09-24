#ifndef DISPLAY_H
#define DISPLAY_H

#include "shop.h"

/*
 * Name: get_option
 * Description: Prompt the user for their numbered option selection
 * Returns (int): The number associated with the option selected by the user
 */
int get_option();

/*
 * Name: execute_option
 * Description: Execute the option selected by the user
 * parameters:
 *		s (shop&): A reference to the shop object
 *		option (int): The user's selected option to execute. Must be
 *			between 1 and 7 (inclusive).
 */
void execute_option(shop& s, int option);

#endif
