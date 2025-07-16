#include "stdio.h"
#include "../headers/init.h"
#include "../headers/map.h"

/*
init
-- the start of the game loop ~~~ 
-- Called ONCE when the game starts!!
*/
void init()
{
    map_parse("test.map");
}