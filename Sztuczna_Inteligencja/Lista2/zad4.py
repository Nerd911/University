from collections import deque
import random

class State:
    def __init__(self, start_pos, end_pos, player_pos, board):
        self.start_pos = start_pos
        self.end_pos = end_pos
        self.board = board
        self.player_pos = player_pos
        self.height = len(board)
        self.width = len(board[0])

    def get_repr(self):
        return frozenset(self.player_pos)

    def __hash__(self):
        return hash(self.get_repr())

    def __eq__(self, other):
        if isinstance(other, State):
            return self.get_repr() == other.get_repr()
        return False

    def is_solved(self):
        for player in self.player_pos:
            if player not in self.end_pos:
                return False
        return True

    def is_move_valid(self, pos, dir):
        new_pos = add_pos(pos, dir)
        if new_pos[0] < 0 or new_pos[1] < 0 or new_pos[0] >= self.height or new_pos[1] >= self.width:
            return False
        return self.board[new_pos[0]][new_pos[1]] != '#'

    def generate_state(self, dir):
        player_pos = set()
        for player in self.player_pos:
            new_pos = player
            if self.is_move_valid(player, dir):
                new_pos = add_pos(player, dir)
            player_pos.add(new_pos)
        return State(self.start_pos, self.end_pos, player_pos, self.board)

    def get_neighbours(self):
        neighbors = []
        for dir in [(-1, 0), (1, 0), (0, 1), (0, -1)]:
            new_state = self.generate_state(dir)
            neighbors.append((new_state, dir))
        return neighbors

directions_dict = {( 1,  0) : "D",
                   (-1,  0) : "U",
                   ( 0,  1) : "R",
                   ( 0, -1) : "L"}

def add_pos(pos1, pos2):
    return (pos1[0] + pos2[0], pos1[1] + pos2[1])

def diff_pos(pos1, pos2):
    return (pos1[0] - pos2[0], pos1[1] - pos2[1])

def construct_path(prev_state_map, cur_state):
    path = []
    while cur_state is not None:
        temp = cur_state
        cur_state, dir = prev_state_map[cur_state]
        if cur_state is not None:
            path.append(directions_dict[dir])
    return list(reversed(path))

def get_step_path(initial_state):
    states_queue = deque([initial_state])
    prev_state_map = {initial_state: (None, None)}
    while len(states_queue) > 0:
        cur_state = states_queue.popleft()
        # cur_state.print_state()
        if cur_state.is_solved():
            return construct_path(prev_state_map, cur_state)
        neighbors = cur_state.get_neighbours()
        for (neighbor, dir) in neighbors:
            # neighbor.print_state()
            if neighbor not in prev_state_map:
                # print("added state")
                prev_state_map[neighbor] = (cur_state, dir)
                states_queue.append(neighbor)
    # print("checkpoint 1")
    return []

def create_random_path(initial_state, n = 20, depth = 5):
    dirx = random.choice([(-1, 0), (1, 0)])
    diry = random.choice([(0, 1), (0, -1)])
    # directions = [(-1, 0), (1, 0), (0, 1), (0, -1)]
    moves = [random.choice([dirx, diry]) for i in range(n)]
    state = initial_state
    end_state = initial_state
    end = 0
    uncertainity = len(initial_state.player_pos)
    for i in range(n):
        state = state.generate_state(moves[i])
        temp = len(state.player_pos)
        if temp < uncertainity:
            uncertainity = temp
            end_state = state
            end = i + 1
    result_path = [directions_dict[move] for move in moves[:end]]
    if(depth > 0 and end < n):
        temp1, temp2 = create_random_path(end_state, n - end, depth - 1)
        result_path = result_path + temp1
        end_state = temp2
    return result_path, end_state

def print_solution(step_path, ofile):
    for step in step_path:
        ofile.write(step)
    ofile.write("\n")

def solve(initial_state, max_uncertainity = 2, max_random_len = 60):
    uncertainity = len(initial_state.player_pos)
    random_path = []
    state = initial_state
    while uncertainity > max_uncertainity:
        random_path, state = create_random_path(initial_state, max_random_len)
        uncertainity = len(state.player_pos)
        # print(uncertainity)
    return random_path + get_step_path(state)

def main():
    with open("zad_input.txt") as ifile:
        with open("zad_output.txt", "w") as ofile:
            board = [list(line[:-1]) for line in ifile]
            player_pos = set()
            start_pos = set()
            end_pos = set()
            for i in range(len(board)):
                for j in range(len(board[i])):
                    if board[i][j] == "S":
                        player_pos.add((i, j))
                        start_pos.add((i, j))
                    elif board[i][j] == "G":
                        end_pos.add((i, j))
                    elif board[i][j] == "B":
                        start_pos.add((i, j))
                        end_pos.add((i, j))
                        player_pos.add((i, j))

            initial_state = State(start_pos, end_pos, player_pos, board)
            step_path = solve(initial_state)
            # print(step_path)
            print_solution(step_path, ofile)

if __name__ == '__main__':
    main()
