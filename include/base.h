#pragma once

// base.h - family aggregator: re-exports the core types, templates and inlines

#include "types/base.h"
#include "types/items.h"

AnimateStatus next_status(AnimateStatus status);
AnimateStatus operator++(AnimateStatus& status, int);
AnimateStatus& operator++(AnimateStatus& status);

#include "templates/base.h"
#include "inlines/base.h"