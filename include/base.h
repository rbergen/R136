#pragma once

#include "types/base.h"

AnimateStatus next_status(AnimateStatus status);
AnimateStatus operator++(AnimateStatus& status, int);
AnimateStatus& operator++(AnimateStatus& status);

const wstring& select_language_param(Language language, const std::vector<const wstring> texts);

#include "templates/base.h"
#include "inlines/base.h"

#define select(...)	select_language_param(core.language, __VA_ARGS__)