#pragma once

// r136.h

#include "types/r136.h"
#include "types/console.h"

extern const char* saved_status_path;

int get_random_number(int max);
AnimateStatus get_random_status(AnimateStatus lowest, AnimateStatus highest);
void run_intro();
bool save_game(CoreData& core);
bool load_game(CoreData& core);
void initialize(CoreData& core);
bool perform_command(CoreData& core);
void force_exit(void);
bool is_room_lit(CoreData& core);
void show_room_status(CoreData& core);
bool progress_animate_status(CoreData& core);
void sleep_ms(int name);
AnimateStatus next_status(AnimateStatus status);
AnimateStatus operator++(AnimateStatus& status, int);
AnimateStatus& operator++(AnimateStatus& status);

extern Console console;

#include "templates/r136.h"
#include "templates/console.h"
#include "inlines/r136.h"
#include "inlines/console.h"