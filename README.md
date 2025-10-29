# C++ Chess Engine (Ichigo)
Ichigo is a C++ chess engine that I built to bridge the intersection between my passion for programming and chess. This project will serve as a tool for exploring various domains of computer science (i.e. OOP, Bitboards, Adverserial Search Algs., Reinforcement learning, Machine Learning, and maybe even systems programming. View this as a space to grow and a playground to practice in the domains that interest me.

Current Features: 
- Full Game logic Implementaions
- Minimax with Alpha Beta Pruning
- Simple CLI for User interaction

The distribution of Ichigo consists of the following files:
* [README.md](./README.md), the file you are currently reading.
* [include/](./include/), a subdirectory containing the header files for the source code
* [src/](./src/), a subdirectory containing the full source code


## Build & Run

### Build
Requirements: CMake ≥ 3.20 and a C++20 compiler (Clang/GCC).
```
# from repo root
cmake -S . -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build -j
```
### Run
```
./build/chess_app       # demo
./build/chess_perft     # perft tool
./build/chess_uci       # UCI engine
./build/chess_tests     # tests

```

