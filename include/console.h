#pragma once

#include "types/console.h"

/* Value that determines the settings for Insert for all functions.
	== 0: Insert off at start, use block cursor to indicate Insert on.
	== 1: Insert on at start, use block cursor to indicate Insert on.
	== 2: Insert off at start, use block cursor to indicate Insert off.
	== 3: Insert on at start, use block cursor to indicate Insert off. */
constexpr int insert_flag = 3;

#include "templates/console.h"
#include "inlines/console.h"
