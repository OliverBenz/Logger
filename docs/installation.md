# Logger installation & integration

## CMake options
- `LOGGER_BUILD_TESTS` (default: `ON` when top level) – build unit tests.
- `LOGGER_BUILD_EXAMPLES` (default: `ON` when top level) – build example apps.
- `LOGGER_ENABLE_INSTALL` (default: `ON` when top level) – emit install/export targets.

## Build locally
```bash
cmake -S . -B build -DLOGGER_BUILD_TESTS=ON -DLOGGER_BUILD_EXAMPLES=ON
cmake --build build
ctest --test-dir build --output-on-failure
```

## Use as a git submodule (pinned, audit-friendly)
1) `git submodule add <repo-url> external/logger`
2) In your root `CMakeLists.txt`:
```cmake
set(LOGGER_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(LOGGER_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
add_subdirectory(external/logger)
target_link_libraries(<your-target> PRIVATE Logger::Logger)
```
- Choose this when you want an auditable, locked revision in your tree.

## Use via FetchContent (easy consumption, automatic download)
```cmake
include(FetchContent)
FetchContent_Declare(
  Logger
  GIT_REPOSITORY <repo-url>
  GIT_TAG        <commit-or-tag>
)
set(LOGGER_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(LOGGER_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(Logger)
target_link_libraries(<your-target> PRIVATE Logger::Logger)
```
- Prefer this when you want simple, on-demand fetching without VCS plumbing.
- Pin `GIT_TAG` to a commit or release; mirror internally if external fetches are blocked.

## Use an installed package (reusable across projects/CI)
```bash
cmake --build build --target install --prefix <install-prefix>
```
```cmake
find_package(Logger CONFIG REQUIRED)
target_link_libraries(<your-target> PRIVATE Logger::Logger)
```

## Integration notes
- Public include path is `Logger/` (e.g., `#include <Logger.hpp>`).
- The library is C++20 and exports an ALIAS target `Logger::Logger`.
- Default output dirs: `${binary_dir}/out/bin` and `${binary_dir}/out/lib`.
- Log rotation writes sequential `(<n>)` suffixed files in the same directory.
