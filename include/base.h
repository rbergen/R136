#pragma once

#include "types/base.h"

AnimateStatus next_status(AnimateStatus status);
AnimateStatus operator++(AnimateStatus& status, int);
AnimateStatus& operator++(AnimateStatus& status);

#include "templates/base.h"
#include "inlines/base.h"