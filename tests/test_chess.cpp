#include <cassert>
#include <string>
#include <iostream>

#include "chess/game.hpp"
#include "chess/board.hpp"
#include "chess/piece.hpp"

using namespace chess;

static bool do_ok(Game& g, const std::string& mv) {
    std::string err;
    bool ok = g.move(mv, err);
    if (!ok) std::cerr << "Expected OK, but got: '" << err << "' for move " << mv << "\n";
    return ok;
}
static bool do_bad(Game& g, const std::string& mv) {
    std::string err;
    bool ok = g.move(mv, err);
    if (ok) std::cerr << "Expected FAIL, but move succeeded: " << mv << "\n";
    return !ok;
}
static char at(const Game& g, int r, int c) {
    const Board& b = g.get_board();
    const Piece* p = b.board[r][c].get();
    if (!p) return '-';
    return p->display().empty() ? '?' : p->display()[0];
}
static Color turn(const Game& g) { return g.side_to_move(); }

void test_initial_setup() {
    Game g;
    for (int c=0;c<8;++c) {
        assert(at(g,1,c) == 'P');
        assert(at(g,6,c) == 'p');
    }
    assert(at(g,0,4) == 'K');
    assert(at(g,0,3) == 'Q');
    assert(at(g,7,4) == 'k');
    assert(at(g,7,3) == 'q');
    assert(turn(g) == Color::White);
}

void test_simple_move_and_turn() {
    Game g;
    assert(do_ok(g, "14 34"));
    assert(at(g,3,4)=='P' && at(g,1,4)=='-');
    assert(turn(g) == Color::Black);
    assert(do_ok(g, "64 44"));
    assert(at(g,4,4)=='p' && at(g,6,4)=='-');
    assert(turn(g) == Color::White);
}

void test_illegal_move_rejected() {
    Game g;
    assert(do_bad(g, "06 26"));
    assert(at(g,0,6)=='N');
    assert(turn(g) == Color::White);
}

void test_en_passant() {
    Game g;
    assert(do_ok(g, "14 34"));
    assert(do_ok(g, "63 43"));
    assert(do_ok(g, "34 44"));
    assert(do_ok(g, "65 45"));
    assert(do_ok(g, "44 55"));
    assert(at(g,5,5) == 'P');
    assert(at(g,4,5) == '-');
    assert(turn(g) == Color::Black);
}

void test_kingside_castling_white() {
    Game g;
    assert(do_ok(g, "06 25"));
    assert(do_ok(g, "60 50"));
    assert(do_ok(g, "14 24"));
    assert(do_ok(g, "67 57"));
    assert(do_ok(g, "05 32"));
    assert(do_ok(g, "61 51"));
    assert(at(g,0,5)=='-');
    assert(at(g,0,6)=='-');
    assert(do_ok(g, "04 06"));
    assert(at(g,0,6) == 'K');
    assert(at(g,0,5) == 'R');
    assert(at(g,0,4) == '-');
    assert(at(g,0,7) == '-');
    assert(turn(g) == Color::Black);
}

void test_deep_copy_independence() {
    Game g;
    Game h = g;
    assert(do_ok(g, "14 34"));
    assert(at(h,1,4) == 'P' && at(h,3,4) == '-');
    assert(at(g,1,4) == '-' && at(g,3,4) == 'P');
}

void test_legal_moves_nonempty_start() {
    Game g;
    auto lm = g.legal_moves();
    assert(!lm.empty());
}

int main() {
    std::cout << "Running tests...\n";
    test_initial_setup();
    test_simple_move_and_turn();
    test_illegal_move_rejected();
    test_en_passant();
    test_kingside_castling_white();
    test_deep_copy_independence();
    test_legal_moves_nonempty_start();
    std::cout << "All tests passed!\n";
    return 0;
}
