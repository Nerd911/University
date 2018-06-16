from collections import deque
import heapq
import random
import sys

class State:
    def __init__(self, start_pos, end_pos, player_pos, board, uncertainity):
        self.start_pos = start_pos
        self.end_pos = end_pos
        self.board = board
        self.player_pos = player_pos
        self.height = len(board)
        self.width = len(board[0])
        self.uncertainity = uncertainity
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

    def get_heuristic_estimate(self):
        player_from_goal_dists = [
            dists_from_goals[pos] for pos in self.player_pos
        ]
        return max(player_from_goal_dists) + int(self.uncertainity * len(self))

    def __get_heuristic_estimate(self):
        result = 0
        for player in self.player_pos:
            if player in self.end_pos:
                continue
            for end in self.end_pos:
                temp = diff_pos(player, end)
                temp_dist = abs(temp[0]) + abs(temp[1])
                if temp_dist > result:
                    result = temp_dist
        # for player in self.player_pos:
        #     min_dist = 100000
        #     for end in self.end_pos:
        #         temp = diff_pos(player, end)
        #         temp_dist = abs(temp[0]) + abs(temp[1])
        #         if temp_dist < min_dist:
        #             min_dist = temp_dist
        #     result += min_dist
        return result

    def generate_state(self, dir):
        player_pos = set()
        for player in self.player_pos:
            new_pos = player
            if self.is_move_valid(player, dir):
                new_pos = add_pos(player, dir)
            player_pos.add(new_pos)
        return State(self.start_pos, self.end_pos, player_pos, self.board, self.uncertainity)

    def get_neighbours(self):
        neighbors = []
        for dir in [(-1, 0), (1, 0), (0, 1), (0, -1)]:
            new_state = self.generate_state(dir)
            neighbors.append((new_state, dir))
        return neighbors

    def __len__(self):
        return len(self.player_pos)

    def __lt__(self, other):
        return len(self) < len(other)

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

def print_solution(step_path, ofile):
    for step in step_path:
        ofile.write(step)
    ofile.write("\n")

def solve(initial_state):
    h = []
    prev_state_map = {initial_state : (None, None)}
    heapq.heappush(h, (0, initial_state))
    gScore = {initial_state : 0}
    fScore = {initial_state : initial_state.get_heuristic_estimate()}
    closedSet = set()

    while len(h) > 0:
        f, current = heapq.heappop(h)
        if current.is_solved():
            return construct_path(prev_state_map, current)
        closedSet.add(current)
        neighbors = current.get_neighbours()
        for (neighbor, dir) in neighbors:
            if neighbor in closedSet:
                continue
            g = gScore[current] + 1
            if neighbor in gScore and g >= gScore[neighbor]:
                continue
            prev_state_map[neighbor] = (current, dir)
            gScore[neighbor] = g
            fScore[neighbor] = g + neighbor.get_heuristic_estimate()
            heapq.heappush(h, (fScore[neighbor], neighbor))
    return []

dists_from_goals = {}
def compute_distances_from_end_points(board, end_pos):
    global dists_from_goals
    dists_from_goals = {pos: 0 for pos in end_pos}
    queue = deque([(pos, 0) for pos in end_pos])
    visited = end_pos.copy()

    while len(queue) > 0:
        pos, dist = queue.popleft()
        for dir in [(-1, 0), (1, 0), (0, 1), (0, -1)]:
            new_pos = add_pos(pos, dir)
            if board[new_pos[0]][new_pos[1]] != '#' and new_pos not in visited:
                visited.add(new_pos)
                dists_from_goals[new_pos] = dist + 1
                queue.append((new_pos, dist + 1))
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
            compute_distances_from_end_points(board, end_pos)
            uncertainity = float(sys.argv[1])
            initial_state = State(start_pos, end_pos, player_pos, board, uncertainity)
            step_path = solve(initial_state)
            # print(step_path)
            print_solution(step_path, ofile)

if __name__ == '__main__':
    main()
