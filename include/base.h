#pragma once

#include "types/base.h"

AnimateStatus next_status(AnimateStatus status);
AnimateStatus operator++(AnimateStatus& status, int);
AnimateStatus& operator++(AnimateStatus& status);

#include "templates/base.h"
#include "inlines/base.h"

#define select(...)	select_language_param(core.language, __VA_ARGS__)
#define get_y_or_n() (tolower(console.main().get_char_input(select("jJnN", "yYnN"))) == select((int)'j', (int)'y'))