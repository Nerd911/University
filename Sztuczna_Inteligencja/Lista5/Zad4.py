import random
import sys
from collections import defaultdict as dd
from turtle import *
from timeit import default_timer as timer
import copy
from  sklearn.neural_network  import MLPClassifier
import  random , pickle
import numpy as np
from sklearn.externals import joblib
#####################################################
# turtle graphic
#####################################################
# tracer(0,1)

BOK = 30
SX = -100
SY = 0
M = 8
MAX = 1
MIN = 0
infinity = 10000000000000
nn = joblib.load('clf.pkl')

def kwadrat(x, y, kolor):
  fillcolor(kolor)
  pu()
  goto(SX + x * BOK, SY + y * BOK)
  pd()
  begin_fill()
  for i in range(4):
    fd(BOK)
    rt(90)
  end_fill()

def kolko(x, y, kolor):
  fillcolor(kolor)

  pu()
  goto(SX + x * BOK + BOK/2, SY + y * BOK - BOK)
  pd()
  begin_fill()
  circle(BOK/2)
  end_fill()

#####################################################

def initial_board():
    B = [ [None] * M for i in range(M)]
    B[3][3] = 1
    B[4][4] = 1
    B[3][4] = 0
    B[4][3] = 0
    return B

class Board:
    dirs  = [ (0,1), (1,0), (-1,0), (0,-1), (1,1), (-1,-1), (1,-1), (-1,1) ]

    def __init__(self, other_board = None):
        if other_board == None:
            self.board = initial_board()
            self.fields = set()
            self.move_list = []
            # self.history = []
            # self.__repr = tuple([item for sublist in seld.board for item in sublist])
            for i in range(M):
                for j in range(M):
                    if self.board[i][j] == None:
                        self.fields.add( (j,i) )
            return
        self.board = [l[:] for l in other_board.board]
        # self.__repr = other_board.__repr
        self.fields = other_board.fields
        self.move_list = other_board.move_list
        # self.history = copy.deepcopy(other_board.history)

    # def get_repr(self):
    #     return self.__repr
    #
    # def __hash__(self):
    #     return hash(self.get_repr())
    #
    # def __eq__(self, other):
    #     if isinstance(other, Board):
    #         return self.get_repr() == other.get_repr()
    #     return False

    def draw(self):
        for i in range(M):
            res = []
            for j in range(M):
                b = self.board[i][j]
                if b == None:
                    res.append('.')
                elif b == 1:
                    res.append('#')
                else:
                    res.append('o')
            print(''.join(res))
        print


    def show(self):
        for i in range(M):
            for j in range(M):
                kwadrat(j, i, 'green')

        for i in range(M):
            for j in range(M):
                if self.board[i][j] == 1:
                    kolko(j, i, 'black')
                if self.board[i][j] == 0:
                    kolko(j, i, 'white')

    def moves(self, player):
        # repr = self.get_repr()
        # if repr in moves_cache[player]:
        #     return moves_cache[player][repr]
        res = []
        for (x,y) in self.fields:
            if any( self.can_beat(x,y, direction, player) for direction in Board.dirs):
                res.append( (x,y) )
        if not res:
            return [None]
        # moves_cache[player][repr] = res
        return res

    def can_beat(self, x,y, d, player):
        dx,dy = d
        x += dx
        y += dy
        cnt = 0
        while self.get(x,y) == 1-player:
            x += dx
            y += dy
            cnt += 1
        return cnt > 0 and self.get(x,y) == player

    def get(self, x,y):
        if 0 <= x < M and 0 <=y < M:
            return self.board[y][x]
        return None

    def do_move(self, move, player):
        # self.history.append([x[:] for x in self.board])
        self.move_list.append(move)

        if move == None:
            return self
        x,y = move
        x0,y0 = move
        self.board[y][x] = player
        self.fields -= set([move])
        for dx,dy in self.dirs:
            x,y = x0,y0
            to_beat = []
            x += dx
            y += dy
            while self.get(x,y) == 1-player:
              to_beat.append( (x,y) )
              x += dx
              y += dy
            if self.get(x,y) == player:
                for (nx,ny) in to_beat:
                    self.board[ny][nx] = player
        # self.__repr = tuple([item for sublist in seld.board for item in sublist])
        return self

    def undo_last_move(self):
        m = self.move_list.pop()
        if m != None:
            self.fields.add(m)

    def result(self):
        res = 0
        for y in range(M):
            for x in range(M):
                b = self.board[y][x]
                if b == 0:
                    res -= 1
                elif b == 1:
                    res += 1
        return res

    def max_value(self, alpha, beta, depth, start_time):
        if self.terminal():
            return 10000*self.result()
        # repr = self.get_repr()
        # if repr in value_cache:
        #     val, depth1 = value_cache[repr]
        #     if depth1 <= depth:
        #         return val
        if self.cut_off_test(depth, start_time):
            val = self.heuristic_value()
            # value_cache[repr] = (val, depth)
            return val
        value = -infinity
        for m in self.moves(1):
            state = Board(self).do_move(m, 1)
            value = max(value, state.min_value(alpha, beta, depth + 1, start_time))
            state.undo_last_move()
            if value >= beta:
                # value_cache[repr] = (value, depth)
                return value
            alpha = max(alpha, value)
        # value_cache[repr] = (value, depth)
        return value

    def min_value(self, alpha, beta, depth, start_time):
        if self.terminal():
            return 10000*self.result()
        # repr = self.get_repr()
        # if repr in value_cache:
        #     val, depth1 = value_cache[repr]
        #     if depth1 <= depth:
        #         return val
        if self.cut_off_test(depth, start_time):
            val = self.heuristic_value()
            # value_cache[repr] = (val, depth)
            return val
        value = infinity
        for m in self.moves(0):
            state = Board(self).do_move(m, 0)
            value = min(value, state.max_value(alpha, beta, depth + 1, start_time))
            state.undo_last_move()
            if value <= alpha:
                # value_cache[repr] = (value, depth)
                return value
            beta = min(beta, value)
        # value_cache[repr] = (value, depth)
        return value

    def alpha_beta_decision(self, player):
        start_time = timer()
        best_move = None
        alpha = -infinity
        beta = infinity
        value = -infinity
        if player == 1:
            for m in self.moves(1):
                state = Board(self).do_move(m, 1)
                tmp = state.min_value(alpha, beta, 1, start_time)
                if tmp > value:
                    best_move = m
                    value = tmp
                state.undo_last_move()
                if value >= beta:
                    # value_cache[repr] = (value, 0)
                    return best_move
                alpha = max(alpha, value)
                if self.cut_off_test(0, start_time):
                    break
        else:
            value = infinity
            for m in self.moves(0):
                state = Board(self).do_move(m, 0)
                if tmp > value:
                    best_move = m
                    value = tmp
                state.undo_last_move()
                if value <= alpha:
                    # value_cache[repr] = (value, 0)
                    return best_move
                beta = min(beta, value)
                if self.cut_off_test(0, start_time):
                    break
        # value_cache[repr] = (value, 0)
        return best_move

    def terminal(self):
        if not self.fields:
            return True
        if len(self.move_list) < 2:
            return False
        return self.move_list[-1] == self.move_list[-2] == None

    def random_move(self, player):
        ms = self.moves(player)
        if ms:
            return random.choice(ms)
        return [None]

    def decision(self, player):
        return max([m for m in self.moves(player)], key = lambda m : Board(self).do_move(m, player).minmax(1 - player, 0, player))

    def cut_off_test(self, depth, start_time):
        return depth > 1 #or timer() - start_time > 0.4

    def minmax(self, player, depth, max_p):
        if self.terminal():
            return 100000*self.result()
        if self.cut_off_test(depth):
            return self.heuristic_value()

        values = [Board(self).do_move(m, 1-player).minmax(1-player, depth+1, max_p) for m in self.moves(player)]
        if player == max_p:
            return max(values)
        else:
            return min(values)

    def disc_count(self):
        return 4 + len(self.move_list)

    def stable_discs_from_empty_corner(self, corner):
        y, x = corner
        if(self.board[y][x] != None):
            return 0
        dx = 1
        dy = 1
        if y == 7:
            dy = -1
        if x == 7:
            dx = -1
        result = 0
        for i in range(y, y+2*dy, dy):
            for j in range(x, x+2*dx, dx):
                if self.board[i][j] == 0:
                    result -= 1
                elif self.board[i][j] == 1:
                    result += 1
        return result

    def corners(self):
        corn = [0, 0]
        for i in [0, 7]:
            for j in [0, 7]:
                if self.board[i][j] != None:
                    corn[self.board[i][j]] += 1

        return 100* (corn[1] - corn[0])/(corn[0] + corn[1] + 1)

    def stability(self):
        self.stable_discs_set = set()
        self.stable_discs_from_corner((0,0), 0)
        self.stable_discs_from_corner((0,7), 0)
        self.stable_discs_from_corner((7,0), 0)
        self.stable_discs_from_corner((7,7), 0)
        player0_stable = len(self.stable_discs_set)
        self.stable_discs_set = set()
        self.stable_discs_from_corner((0,0), 1)
        self.stable_discs_from_corner((0,7), 1)
        self.stable_discs_from_corner((7,0), 1)
        self.stable_discs_from_corner((7,7), 1)
        player1_stable = len(self.stable_discs_set)
        return player1_stable - player0_stable

    def stable_discs_from_corner(self, corner, player):
        y, x = corner
        dx = 1
        dy = 1
        limx = 8
        limy = 8
        if y == 7:
            dy = -1
            limy = -1
        if x == 7:
            sx = -1
            limx = -1
        for i in range(y, limy, dy):
            if self.board[i][x] != player:
                break
            for j in range(x, limx, dx):
                if self.board[i][j] != player or (i, j) in self.stable_discs_set:
                    break
                self.stable_discs_set.add((i, j))
    def mobility(self):
        player0_moves = len(self.moves(0))
        player1_moves = len(self.moves(1))
        return 100 * (player0_moves - player1_moves) / (player0_moves + player1_moves + 1)

    def corners_potential(self):
        result = 0
        for corner in [(0,0), (0, 7), (7, 0), (7, 7)]:
            result += self.stable_discs_from_empty_corner(corner)
        return result

    def heuristic_value(self):
        X = [self.get_coefficients()]
        res = nn.predict_proba(X)
        return 100000 * res[0][0]*nn.classes_[0] + 100000*res[0][1]*nn.classes_[1]

    def get_coefficients(self):
        return [self.result(), self.mobility(), self.corners(), self.stability(), self.corners_potential()]

def play():
    player = 0
    B = Board()
    m = None
    while True:
        # B.draw()
        # B.show()
        if player == 0:
            m = B.random_move(player)
        else:
            m = B.alpha_beta_decision(player)
        B.do_move(m, player)
        player = 1-player
        # input()
        if B.terminal():
            break

        # B.draw()
        # B.show()
        # print('Result', B.result())
    return B.result()

cntr = 0
for i in range(100):
    if play() < 0:
        cntr += 1
print(cntr)
sys.exit(0)
