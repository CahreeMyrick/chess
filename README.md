Chess Engine (UCI)

A small C++ chess engine with:

a playable game model (Game, Board, Piece, …)

a simple minimax search (MinimaxStrategy)

a UCI front-end (chess_uci)

a perft tool for correctness/benchmarks (chess_perft)

optional tests (chess_tests)

The project is built with CMake and C++20.

Project Layout
chess/
├─ CMakeLists.txt
├─ include/
│  └─ chess/…                    # headers (types, piece, board, game, strategy, eval)
├─ src/
│  ├─ piece.cpp
│  ├─ board.cpp
│  ├─ game.cpp
│  ├─ strategy_minimax.cpp
│  ├─ eval.cpp
│  └─ main.cpp                   # CLI (menu) -> target: chess_app
└─ tools/
   ├─ perft.cpp                  # perft driver -> target: chess_perft
   ├─ uci_main.cpp               # UCI main    -> target: chess_uci
   └─ test_chess.cpp             # basic tests -> target: chess_tests (optional)

Build (CMake)
# Configure (use Release for fair performance numbers)
cmake -S . -B build -DCMAKE_BUILD_TYPE=Release

# Build all targets
cmake --build build -j

(Optional) Enable LTO/IPO

Add this to your CMakeLists.txt (top-level) to enable link-time optimization when supported:

include(CheckIPOSupported)
check_ipo_supported(RESULT HAVE_IPO OUTPUT IPO_ERR)
if(HAVE_IPO)
  message(STATUS "IPO/LTO enabled")
  set(CMAKE_INTERPROCEDURAL_OPTIMIZATION ON)
endif()


On Clang/GCC you may also want to pass -O3 -DNDEBUG -march=native (already added for the chess library in this repo).

Run

All executables are emitted under build/ (or your generator’s default bin directory).

# CLI game (menu-driven)
./build/chess_app

# Perft (prints nodes/time/NPS; exits non-zero on mismatch with known counts)
./build/chess_perft

# UCI engine (talk to a GUI or the terminal)
./build/chess_uci

Example UCI session
uci
id name MyEngine
id author You
uciok
isready
readyok
ucinewgame
position startpos moves e2e4 e7e5 g1f3
go depth 3
bestmove g1f3

Move Formats

External (UCI): e2e4, e7e8q, …

Internal (engine): two digit pairs "rc rc" with r,c ∈ {0..7}.
Example: "14 34" means (r=1,c=4) → (r=3,c=4) i.e., e2 → e4.

The UCI front-end converts between UCI and the engine’s internal format.

Correctness (Known Perft Baselines)

These are the standard node counts used to validate move generation:

startpos:
d1 = 20, d2 = 400, d3 = 8,902, d4 = 197,281

kiwipete:
d1 = 48, d2 = 2,039, d3 = 97,862, d4 = 4,085,603

chess_perft checks against these values (you can

You said:
it should be a markdown file
ChatGPT said:
# Chess Engine (UCI)

A small C++ chess engine with:

- a playable game model (`Game`, `Board`, `Piece`, …)
- a simple minimax search (`MinimaxStrategy`)
- a UCI front-end (`chess_uci`)
- a perft tool for correctness/benchmarks (`chess_perft`)
- optional tests (`chess_tests`)

Built with **CMake** and **C++20**.

---

## Project Layout



chess/
├─ CMakeLists.txt
├─ include/
│ └─ chess/… # headers (types, piece, board, game, strategy, eval)
├─ src/
│ ├─ piece.cpp
│ ├─ board.cpp
│ ├─ game.cpp
│ ├─ strategy_minimax.cpp
│ ├─ eval.cpp
│ └─ main.cpp # CLI (menu) -> target: chess_app
└─ tools/
├─ perft.cpp # perft driver -> target: chess_perft
├─ uci_main.cpp # UCI main -> target: chess_uci
└─ test_chess.cpp # basic tests -> target: chess_tests (optional)


---

## Build (CMake)

```bash
# Configure (use Release for fair performance numbers)
cmake -S . -B build -DCMAKE_BUILD_TYPE=Release

# Build all targets
cmake --build build -j


Tip: If you change compilers (e.g., Clang ↔︎ GCC), do a clean configure:
rm -rf build && cmake -S . -B build -DCMAKE_BUILD_TYPE=Release.

Optional: Enable LTO/IPO

Add this to the top-level CMakeLists.txt to enable link-time optimization when supported:

include(CheckIPOSupported)
check_ipo_supported(RESULT HAVE_IPO OUTPUT IPO_ERR)
if(HAVE_IPO)
  message(STATUS "IPO/LTO enabled")
  set(CMAKE_INTERPROCEDURAL_OPTIMIZATION ON)
endif()


On Clang/GCC you may also want flags like -O3 -DNDEBUG -march=native.
This project already applies optimized flags to the chess library.

Run

Executables are emitted under build/ (or your generator’s default bin dir).

# CLI game (menu-driven)
./build/chess_app

# Perft (prints nodes/time/NPS; exits non-zero on mismatch with known counts)
./build/chess_perft

# UCI engine (talk to a GUI or to the terminal)
./build/chess_uci

Example UCI session
uci
id name MyEngine
id author You
uciok
isready
readyok
ucinewgame
position startpos moves e2e4 e7e5 g1f3
go depth 3
bestmove g1f3

Move Formats

External (UCI): e2e4, e7e8q, …

Internal (engine): two digit pairs "rc rc" with r,c ∈ {0..7}.
Example: "14 34" means (r=1,c=4) → (r=3,c=4) i.e., e2 → e4.

The UCI front-end converts between UCI and the engine’s internal format.

Correctness (Known Perft Baselines)

These standard node counts validate move generation:

startpos:
d1 = 20, d2 = 400, d3 = 8,902, d4 = 197,281

kiwipete:
d1 = 48, d2 = 2,039, d3 = 97,862, d4 = 4,085,603

chess_perft compares against these values (you can raise the depths locally).

Benchmarks

Performance varies with CPU/OS/compiler/flags. Use:

./build/chess_perft

startpos d=1  nodes=20      time=0.290208 ms  (68916 nps)
startpos d=2  nodes=400     time=6.75079 ms   (59252 nps)
startpos d=3  nodes=8902    time=73.5181 ms   (121085 nps)
startpos d=4  nodes=197281  time=1292.92 ms   (152586 nps)

kiwipete d=1  nodes=48      time=0.284583 ms  (168667 nps)
kiwipete d=2  nodes=2039    time=12.5899 ms   (161955 nps)
kiwipete d=3  nodes=97862   time=526.267 ms   (185954 nps)
kiwipete d=4  nodes=4085603 time=24281.2 ms   (168262 nps)


These match the node counts of the baselines above. NPS (nodes/sec) depends on your machine and build type.

Environment info here:

Compiler: (e.g., Apple Clang 16 / GCC 13)

Build Type: Release (LTO on/off)

Flags: -O3 -DNDEBUG -march=native (if applicable)

CPU/RAM/OS: (e.g., Apple M3 / 16 GB / macOS 15.x)

Threads: 1 (engine is single-threaded)