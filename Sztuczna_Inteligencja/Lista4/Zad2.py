import copy
import random
from timeit import default_timer as timer

# from __future__ import print_function
BOARD = ["..#*#..",
         "...#...",
         ".......",
         ".~~.~~.",
         ".~~.~~.",
         ".~~.~~.",
         ".......",
         "...#...",
         "..#*#.."]

RAT      = 0
CAT      = 1
DOG      = 2
WOLF     = 3
JAGUAR   = 4
TIGER    = 5
LION     = 6
ELEPHANT = 7

HEIGHT = 9
WIDTH = 7

infinity = 10000000000000

VALUES = {
          "R" : RAT,      "r" : RAT,
          "C" : CAT,      "c" : CAT,
          "D" : DOG,      "d" : DOG,
          "W" : WOLF,     "w" : WOLF,
          "J" : JAGUAR,   "j" : JAGUAR,
          "T" : TIGER,    "t" : TIGER,
          "L" : LION,     "l" : LION,
          "E" : ELEPHANT, "e" : ELEPHANT,
         }
def initial_board():
    result = [None, None]
    result[0] = {
        (0, 0) : 'L',
        (0, 6) : 'T',
        (1, 1) : 'D',
        (1, 5) : 'C',
        (2, 0) : 'R',
        (2, 2) : 'J',
        (2, 4) : 'W',
        (2, 6) : 'E'
    }
    result[1] = {
        (8, 6) : 'l',
        (8, 0) : 't',
        (7, 1) : 'd',
        (7, 5) : 'c',
        (6, 6) : 'r',
        (6, 4) : 'j',
        (6, 2) : 'w',
        (6, 0) : 'e'
    }
    return result


def add_pos(pos0, pos1):
    return (pos0[0] + pos1[0], pos0[1] + pos1[1])
def manhattan_distance(pos0, pos1):
    return abs(pos0[0] - pos1[0]) + abs(pos0[1] - pos1[1])
value_cache = {}
class State:
    dirs  = [ (0,1), (1,0), (-1,0), (0,-1)]

    def __init__(self, other_board = None, move_list = None):
        if other_board == None:
            self.player_figures = initial_board()
            self.__repr = (frozenset(self.player_figures[0]), frozenset(self.player_figures[1]))
            self.move_list = []
            self.__moves = [None, None]
            return
        self.player_figures= copy.deepcopy(other_board.player_figures)
        self.__repr = other_board.__repr
        self.__moves = other_board.__moves
        if move_list == None:
            self.move_list = other_board.move_list
            return
        self.move_list = move_list

    def get_repr(self):
        return self.__repr

    def __hash__(self):
        return hash(self.get_repr())

    def __eq__(self, other):
        if isinstance(other, State):
            return self.get_repr() == other.get_repr()
        return False

    def get_fig(self, pos, player):
        return self.player_figures[player][pos]

    def is_move_valid(self, pos, dir, player):
        new_pos = add_pos(pos, dir)
        if new_pos[0] >= HEIGHT or new_pos[0] < 0 or new_pos[1] >= WIDTH or new_pos[1] < 0:
            return False
        if new_pos == (0, 3) and player == 0 or new_pos == (8, 3) and player == 1:
            return False
        if self.is_occupied_by_player(new_pos, player):
            return False
        if self.is_water(new_pos):
            fig = self.get_fig(pos, player)
            if VALUES[fig] == RAT:
                return True
            if VALUES[fig] == TIGER or VALUES[fig] == LION:
                return self.can_jump_over_water(pos, dir, player)
            return False
        if self.is_occupied_by_enemy(new_pos, player):
            return self.enemy_can_be_beaten(pos, new_pos, player)
        return True

    def is_occupied_by_player(self, pos, player):
        return pos in self.player_figures[player]

    def is_occupied_by_enemy(self, pos, player):
        return pos in self.player_figures[1-player]

    def enemy_can_be_beaten(self, pos, new_pos, player):
        fig = self.get_fig(pos, player)
        enemy = self.get_fig(new_pos, 1 - player)
        if VALUES[fig] == RAT and self.is_water(pos) and not self.is_water(new_pos):
            return False
        return VALUES[fig] >= VALUES[enemy] or BOARD[new_pos[0]][new_pos[1]] == '#' or VALUES[fig] == RAT and VALUES[enemy] == ELEPHANT

    def is_water(self, pos):
        return BOARD[pos[0]][pos[1]] == '~'

    def can_jump_over_water(self, pos, dir, player):
        new_pos = add_pos(pos, dir)
        while self.is_water(new_pos):
            if self.is_occupied_by_enemy(new_pos, player):
                return False
            new_pos = add_pos(new_pos, dir)
        if self.is_occupied_by_enemy(new_pos, player):
            return self.enemy_can_be_beaten(pos, new_pos, player)
        return True

    def moves(self, player):
        if self.__moves[player] != None:
            return self.__moves[player]
        res = []
        for pos, figure in self.player_figures[player].items():
            for dir in self.dirs:
                if self.is_move_valid(pos, dir, player):
                    res.append((pos, dir))
        self.__moves[player] = res
        return res

    def get(self, x,y):
        if 0 <= x < M and 0 <=y < M:
            return self.board[y][x]
        return None

    def do_move(self, move, player):
        # self.history.append([x[:] for x in self.board])
        self.move_list.append(move)
        # print(move)
        if move == None:
            return self
        # # print(move)
        # if len(move) == 1:
        #     print(move)
        pos, dir = move
        fig = self.get_fig(pos, player)
        new_pos = add_pos(pos, dir)
        while (VALUES[fig] == LION or VALUES[fig] == TIGER) and self.is_water(new_pos):
            new_pos = add_pos(new_pos, dir)
        self.player_figures[player].pop(pos)
        self.player_figures[player][new_pos] = fig
        if new_pos in self.player_figures[1-player]:
            self.player_figures[1-player].pop(new_pos)
        self.__repr = (frozenset(self.player_figures[0]), frozenset(self.player_figures[1]))
        self.__moves = [None, None]
        return self

    def result(self):
        if (8, 3) in self.player_figures[0]:
            return -1
        if (0, 3) in self.player_figures[1]:
            return 1
        return 0

    def terminal(self):
        if self.result() != 0:
            return True
        if len(self.move_list) < 2:
            return False
        return self.move_list[-1] == self.move_list[-2] == None

    def random_move(self, player):
        ms = self.moves(player)
        if ms:
            return random.choice(ms)
        return None

    def random_play(self, moves_left, player):
        cntr = 0
        while not self.terminal() and cntr < moves_left:
            m = self.random_move(player)
            self.do_move(m, player)
            player = 1-player
            cntr += 1
        return (self.result(), cntr)

    def naive_score(self, player, limit):
        result = 0
        while limit > 0:
            # print(limit)
            temp, cntr = self.random_play(limit, player)
            result += temp
            if cntr == 0:
                break
            limit -= cntr
        return result

    def naive_agent(self, player, limit):
        if self.moves(player) == []:
            return None
        if player == 0:
            return min([m for m in self.moves(player)], key = lambda m : State(self, self.move_list[:]).do_move(m, player).naive_score(player, limit))
        return max([m for m in self.moves(player)], key = lambda m : State(self, self.move_list[:]).do_move(m, player).naive_score(player, limit))

    def cut_off_test(self, depth):
        return depth > 1

    def max_value(self, alpha, beta, depth):
        if self.terminal():
            return 20000*self.result()
        repr = self.get_repr()
        if repr in value_cache:
            val, depth1 = value_cache[repr]
            if depth1 <= depth:
                return val
        if self.cut_off_test(depth):
            val = self.heuristic_value()
            value_cache[repr] = (val, depth)
            return val
        value = -infinity
        for m in self.moves(1):
            state = State(self).do_move(m, 1)
            value = max(value, state.min_value(alpha, beta, depth + 1))
            state.undo_last_move()
            if value >= beta:
                value_cache[repr] = (value, depth)
                return value
            alpha = max(alpha, value)
        value_cache[repr] = (value, depth)
        return value
    def undo_last_move(self):
        m = self.move_list.pop()
    def min_value(self, alpha, beta, depth):
        if self.terminal():
            return 10000*self.result()
        repr = self.get_repr()
        if repr in value_cache:
            val, depth1 = value_cache[repr]
            if depth1 <= depth:
                return val
        if self.cut_off_test(depth):
            val = self.heuristic_value()
            value_cache[repr] = (val, depth)
            return val
        value = infinity
        for m in self.moves(0):
            state = State(self).do_move(m, 0)
            value = min(value, state.max_value(alpha, beta, depth + 1))
            state.undo_last_move()
            if value <= alpha:
                value_cache[repr] = (value, depth)
                return value
            beta = min(beta, value)
        value_cache[repr] = (value, depth)
        return value

    def alpha_beta_decision(self, player):
        best_move = None
        alpha = -infinity
        beta = infinity
        value = -infinity
        if player == 1:
            for m in self.moves(1):
                state = State(self).do_move(m, 1)
                tmp = state.min_value(alpha, beta, 1)
                if tmp > value:
                    best_move = m
                    value = tmp
                state.undo_last_move()
                if value >= beta:
                    value_cache[repr] = (value, 0)
                    return best_move
                alpha = max(alpha, value)
        else:
            value = infinity
            for m in self.moves(0):
                state = State(self).do_move(m, 0)
                tmp = state.max_value(alpha, beta, 1)
                if tmp < value:
                    best_move = m
                    value = tmp
                state.undo_last_move()
                if value <= alpha:
                    value_cache[repr] = (value, 0)
                    return best_move
                beta = min(beta, value)
        value_cache[repr] = (value, 0)
        return best_move

    def figure_balance(self):
        return len(self.player_figures[1]) - len(self.player_figures[0])

    def figure_values_balance(self):
        result = 0;
        for figure in self.player_figures[1].values():
            result += (VALUES[figure] + 1)
        for figure in self.player_figures[0].values():
            result -= (VALUES[figure] + 1)
        return result

    def distance_balance(self):
        dist0 = min(manhattan_distance(pos, (8, 3)) for pos in self.player_figures[0]) if len(self.player_figures[0]) > 0 else 16
        dist1 = min(manhattan_distance(pos, (0, 3)) for pos in self.player_figures[1]) if len(self.player_figures[1]) > 0 else 16
        # for pos in self.player_figures[1]:
        #     dist1 = max(13 - manhattan_distance(pos, (0, 3)), dist1)
        # for pos in self.player_figures[0]:
        #     dist0 = max(13 - manhattan_distance(pos, (8, 3)), dist0)
        return (dist0 - dist1)

    def heuristic_value(self):
        if self.terminal():
            return self.result() * 10000
        # print("figure_values_balance: {}".format(self.figure_values_balance()))
        # print("distance_balance: {}".format(self.distance_balance()))
        return 100*self.figure_values_balance() + 200*self.distance_balance()

    def display(self):
        for i in range(9):
            line = ""
            for j in range(7):
                if (i, j) in self.player_figures[0]:
                    line += self.player_figures[0][(i, j)]
                    continue
                if (i, j) in self.player_figures[1]:
                    line += self.player_figures[1][(i, j)]
                    continue
                line += BOARD[i][j]
            # print(line)
def play():
    player = 0
    B = State()
    m = None
    while True:
        # B.draw()
        # B.show()
        if player == 0:
            # print("\nnaive")
            # print(B.moves(player))
            begin = timer()
            m = B.naive_agent(0, 20000)
            # print("naive_agent: {}".format(timer() - begin))
        else:
            # print("\nalpha-beta")
            # print(B.moves(player))
            begin = timer()
            m = B.alpha_beta_decision(player)
            # print("alpha_beta_agent: {}".format(timer() - begin))
        # print(B.heuristic_value())
        B.do_move(m, player)
        player = 1-player
        # B.display()
        # input()
        if B.terminal():
            break
    return B.result()

cntr = 0
for i in range(10):
    if play() < 0:
        cntr += 1
print(cntr)
