#ifndef TEXTURE_MANAGER_H
#define TEXTURE_MANAGER_H

#include <stdio.h>
#include "raylib.h"
#include "./defs.h"

typedef struct {
    char name[64];
    Texture2D texture;

} TextureCacheEntry;

extern int texture_cache_count;
extern TextureCacheEntry texture_cache[MAX_TEXTURES];
extern Texture2D default_texture;

Texture2D texture_get_cached(char *texture_name);
Texture2D texture_get_default();

#endif // TEXTURE_MANAGER_H