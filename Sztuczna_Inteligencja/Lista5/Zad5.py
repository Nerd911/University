import sys
POSSIBLE_DIRS = [(x, y) for x in [-1, 0, 1] for y in [-1, 0, 1]]
v_opt_cache = {}
class Car:
    def __init__(self, board):
        self.board = board
        self.height = len(board)
        self.width = len(board[0])

    def do_move(self, state, move):
        x, y, vx, vy = state
        dvx, dvy = move
        vx += dvx
        vy += dvy
        if vx > 3: vx = 3
        if vy > 3: vy = 3
        if vx < -3: vx = -3
        if vy < -3: vy = -3
        x += vx
        y += vy
        return (x, y, vx, vy)

    def evaluate_state(self, state):
        x, y, vx, vy = state
        try:
            if y < 0 or x < 0 or y >= self.height or x >= self.width:
                return -100
            if self.board[y][x] == '.':
                return -100
            if self.board[y][x] == 'e':
                return 100
            return 0
        except IndexError as e:
            print(board)
            print("{} {}".format(x, y))
            print("{} {}".format(width, height))
            exit()

    def terminal(self, state):
        return self.evaluate_state(state) != 0

    def actions(self, state):
        if self.terminal(state):
            return []
        return POSSIBLE_DIRS
    def __is_oil(self, state):
        return self.board[state[1]][state[0]] == 'o'

    def __get_oil_actions(self, action):
        return [(action[0] + x, action[1] + y) for x in [-1, 0, 1] for y in [-1, 0, 1]]

    def possible_states(self, state, action):
        actions = [action]
        if self.__is_oil(state):
            actions = self.__get_oil_actions(action)
        return [self.do_move(state, action) for action in actions]

sys.setrecursionlimit(2000)
def get_all_states(board):
    height = len(board)
    width = len(board[0])
    return [(x, y, vx, vy) for y in range(-3, height + 3) for x in range(-3, width+3) for vx in range(-3, 4) for vy in range(-3, 4)]

def value_iteration(car, states, epsilon=0.001, gamma = 0.9):
    U1 = dict([(s, 0) for s in states])
    while True:
        U = U1.copy()
        delta = 0
        for s in states:
            actions = car.actions(s)
            states_mapping = [car.possible_states(s, a) for a in actions]
            U1[s] = car.evaluate_state(s) + gamma * (max([sum([U[s1]/float(len(s2)) for s1 in s2]) for s2 in states_mapping if len(s2) > 0]) if len(states_mapping) > 0 else 0)
            delta = max(delta, abs(U1[s] - U[s]))
        if delta < epsilon * (1 - gamma) / gamma:
             return U
def best_policy(car, U, states):
    pi = {}
    for s in states:
        actions = car.actions(s)
        pi[s] = max(actions, key = lambda a:expected_utility(a, s, U, car)) if len(actions) > 0 else None
    return pi

def expected_utility(a, s, U, car):
    possible_states = car.possible_states(s, a)
    return sum([U[s1]/float(len(possible_states)) for s1 in possible_states])

for i in [1, 2, 3, 6, 8, 9, 10, 11]:
    with open("chars_test1/task{}.txt".format(i)) as ifile:
        with open("chars_test1/policy_for_task{}.txt".format(i), "w") as ofile:
            v_opt_cache = {}
            board = [line[:-1] for line in ifile][:-1]
            start = None
            for i in range(0, len(board)):
                for j in range(0, len(board[i])):
                    if board[i][j] == 's':
                        start = (j, i)
            car = Car(board)
            states = get_all_states(board)
            U = value_iteration(car, states)
            p = best_policy(car, U, states)
            for state in states:
                action = p[state]
                if action == None:
                    continue
                ofile.write("{} {} {} {}     {} {}\n".format(state[0], state[1], state[2], state[3], action[0], action[1]))
