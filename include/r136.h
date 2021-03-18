#pragma once

// r136.h

#include "types/base.h"
#include "types/console.h"

bool progress_animates(CoreData& core);
bool perform_command(CoreData& core);

AnimateStatus next_status(AnimateStatus status);
AnimateStatus operator++(AnimateStatus& status, int);
AnimateStatus& operator++(AnimateStatus& status);

extern Console console;

#include "templates/base.h"
#include "templates/console.h"
#include "inlines/base.h"
#include "inlines/console.h"