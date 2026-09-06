# Include architecture

This directory uses a layered header layout whose goal is to keep each
translation unit compiling only the code it actually needs. A compilation unit
(CU) that merely *names* a type in a function signature should not have to
compile that type's inline bodies, template definitions, or data tables.

To achieve that, most modules are split by *aspect* across parallel
subdirectories, with a single flat "entry point" header per module at the top of
`include/`.

## The aspect layers

| Location          | Contains                                                        | Depends on            |
|-------------------|----------------------------------------------------------------|-----------------------|
| `types/X.h`       | Declarations only: `struct`/`class`/`enum`, method signatures  | other `types/*.h`     |
| `templates/X.h`   | Template function / method **definitions**                     | `types/*.h`           |
| `inlines/X.h`     | `inline` function / method **definitions**                     | `types/*.h`, `templates/*.h` |
| `data/X.h`        | Data-table definitions, `#include`d **inside a function body**  | an umbrella header    |
| `X.h` (flat)      | The module entry point (see two kinds below)                   | its own aspect files  |

Not every module has all four aspects. A module with no inline or template code
(e.g. `animates`) has only `types/animates.h` behind its umbrella; that is
expected, not an omission.

## The two kinds of flat header

A header directly under `include/` is one of two things. They look alike but
play opposite roles, so know which you are reaching for:

1. **Family aggregators** — `base.h`, `items.h`, `console.h`, `general.h`,
   `random.h`. These re-export a family's aspect files (`types` + `templates` +
   `inlines`) so a CU can pull in the whole module with one include.

2. **Service interfaces** — `actions.h`, `commands.h`, `gamedata.h`,
   `status.h`, `startup.h`, `parser.h`. Each is the public API of one
   `src/*.cpp`: a namespace of free functions (or a class) operating on
   `CoreData`. They include only `types/base.h`, because they just need to name
   the types their signatures mention — not compile any bodies.

## Rules

- **CU (`.cpp`) code includes flat headers only.** Never include a
  `types/`, `templates/`, or `inlines/` header directly from a `.cpp`; go
  through the family aggregator or service interface. The aspect
  subdirectories are an implementation detail of the flat headers.
- **A family aggregator includes every aspect file the family has.** If you
  add, say, `templates/foo.h` to an existing family, add it to `foo.h` too.
- **Keep `types/*.h` free of bodies.** Put inline bodies in `inlines/` and
  template bodies in `templates/`. This is what keeps `types/base.h` cheap
  enough to be the common dependency of every service interface.
- **Prefer a forward declaration over an include in `types/*.h`.** If a type is
  only used by pointer or reference, forward-declare it and let the umbrella
  header pull in the full definition. (This is why `types/base.h`
  forward-declares `Flashlight` instead of including `types/items.h`, which
  would create a cycle.)
- **`data/*.h` files are intentionally guard-less** and are `#include`d inside a
  function scope (see the bottom of `src/startup.cpp`). Every other header
  carries `#pragma once`.

## Finding the header for a piece of CU code

- Need to *call* a service (load a game, parse input, run a command)? Include
  that service's flat header: `gamedata.h`, `parser.h`, `commands.h`, ...
- Need to *name or use* a core type (`CoreData`, `Item`, an enum)? Include
  `base.h`.
- Need a concrete `Item` subclass or the item helpers? Include `items.h`.
- Working on an animate / console / RNG? Include `animates.h` / `console.h` /
  `random.h`.

If you are editing a type and need to find all of its parts, remember one module
can span up to four files: `types/X.h` (shape), `templates/X.h` and
`inlines/X.h` (behaviour), and `data/X.h` (instances).
