#include <nds.h>
#include <stdio.h>
#include <sys/dir.h>
#include <fat.h>
#include <dirent.h>
#include <string.h>

#include "sound.h"
#include "timer_muter.h"

#define STORAGE_FILE_PATH "/storage.txt"

/*
    * Initializes the storage system.
*/
void init_storage();

/*
    * Apply the default parameters if params.txt exists.
*/
void apply_default_params();

/*
    * Save the current parameters to params.txt.
*/
void save_default_params();