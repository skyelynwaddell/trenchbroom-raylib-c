#include "../headers/cleanup.h"
#include "../headers/map.h"

/*
clean_up
-- clean up event called when the game ends
-- and in between level changes -- possibly portal changes
-- put any garbage collection in here
*/
void clean_up()
{
    map_clear_models(); //clears all the map models cache from memory

}