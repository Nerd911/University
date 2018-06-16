import heapq
import itertools
from collections import deque

cached_available = {}
fail_cntr = 1
class State:
    def __init__(self, player, boxes, board, boxes_left):
        self.player = player
        self.boxes = boxes
        self.board = board
        self.boxes_left = boxes_left
        self.height = len(board)
        self.width = len(board[0])
        global cached_available
        key = (frozenset(boxes), player)
        if key not in cached_available:
            self.__getavailable()
        # else:
        #     print("cached")
        self.available_pos = cached_available[key]
        # print(boxes_left)
        # print("checkpoint1")

    def __getavailable(self):
        result = set()
        q = deque()
        q.append(self.player)
        processed = set(self.player)
        global cached_available
        while len(q) > 0:
            pos = q.popleft()
            for dir in [(-1, 0), (1, 0), (0, 1), (0, -1)]:
                new_pos = add_pos(pos, dir)
                if new_pos in self.boxes and new_pos not in processed:
                    result.add(pos)
                elif (self.board[new_pos[0]][new_pos[1]] == '.' or self.board[new_pos[0]][new_pos[1]] == 'G') and new_pos not in processed:
                    processed.add(new_pos)
                    q.append(new_pos)
        boxes_set = frozenset(self.boxes)
        result = frozenset(result)
        for pos in processed:
            cached_available[(boxes_set, pos)] = result
        cached_available[(boxes_set, self.player)] = result

    def construct_path(self, goal):
        prev_state_map = {self.player : None}
        q = deque([self.player])
        while len(q) > 0:
            cur = q.popleft()
            if cur == goal:
                break
            for dir in [(-1, 0), (1, 0), (0, 1), (0, -1)]:
                new_pos = add_pos(cur, dir)
                if new_pos in prev_state_map:
                    continue
                if new_pos == goal:
                    prev_state_map[goal] = cur
                    q.appendleft(goal)
                    break
                if self.__is_valid_position(new_pos):
                    prev_state_map[new_pos] = cur
                    q.append(new_pos)
        path = []
        cur = goal
        while cur is not None:
            temp = cur
            cur = prev_state_map[cur]
            if cur is not None:
                path.append(directions_dict[diff_pos(temp, cur)])
        return list(reversed(path))

    def print_board(self):
        for row in self.board:
            for col in row:
                print(col, end = "")
            print("")

    def print_state(self):
        for i in range(self.height):
            for j in range(self.width):
                if (i, j) == self.player:
                    print("K", end="")
                elif (i, j) in self.boxes:
                    print("B",end="")
                else:
                    print(self.board[i][j], end = "")
            print("")
        # print("Player: {}".format(self.player))
        # print("Boxes: {}".format(self.boxes))
        print("Boxes left: {}".format(self.boxes_left))
        # self.print_board()

    def get_repr(self):
        return (self.available_pos, frozenset(self.boxes))

    def __hash__(self):
        return hash(self.get_repr())

    def __eq__(self, other):
        if isinstance(other, State):
            return self.get_repr() == other.get_repr()
        return False

    def is_solved(self):
        return self.boxes_left == 0

    def __is_valid_position(self, pos):
        return not (pos[0] < 0 or pos[1] < 0 or pos[0] >= self.height or pos[1] >= self.width or pos in self.boxes or self.board[pos[0]][pos[1]] == 'W')

    def is_move_valid(self, box, dir):
        new_pos = add_pos(box, dir)
        if not self.__is_valid_position(new_pos):
            return False
        # print("Checkpoint2")
        player_pos = diff_pos(box, dir)
        return player_pos in self.available_pos

    def generate_state(self, box, dir):
        new_pos = add_pos(box, dir)
        boxes = self.boxes[:]
        boxes[boxes.index(box)] = new_pos
        boxes_left = self.boxes_left + int(self.board[box[0]][box[1]] == 'G') - int(self.board[new_pos[0]][new_pos[1]] == 'G')
        return State(box, boxes, self.board, boxes_left)

    def get_neighbours(self):
        neighbors = []
        l = len(self.boxes)
        for box in self.boxes:
            for dir in [(-1, 0), (1, 0), (0, 1), (0, -1)]:
                if self.is_move_valid(box, dir):
                    new_state = self.generate_state(box, dir)
                    neighbors.append((new_state, dir))
            # else:
            #     print("Player: {} Boxes: {} Dir: {}".format(self.player, self.boxes, dir))
        return neighbors

    def __lt__(self, other):
        return self.boxes_left < other.boxes_left

directions_dict = {( 1,  0) : "D",
                   (-1,  0) : "U",
                   ( 0,  1) : "R",
                   ( 0, -1) : "L"}

def add_pos(pos1, pos2):
    return (pos1[0] + pos2[0], pos1[1] + pos2[1])

def diff_pos(pos1, pos2):
    return (pos1[0] - pos2[0], pos1[1] - pos2[1])

def construct_path(prev_state_map, cur_state):
    # print("construct_path")
    path = []
    while cur_state is not None:
        # cur_state.print_state()
        temp_state = cur_state
        cur_state, dir = prev_state_map[cur_state]
        if cur_state is not None:
            goal = diff_pos(temp_state.player, dir)
            # print(goal)
            # print(cur_state.construct_path(goal) + [directions_dict[dir]])
            path = cur_state.construct_path(goal) + [directions_dict[dir]] + path
    return path

def dist(pos0, pos1):
    return abs(pos0[0] - pos1[0]) + abs(pos0[1] - pos1[1])

def sum_dist(positions0, positions1):
    l = len(positions0)
    return sum([dist(positions0[i], positions1[i]) for i in range(l)])

def heuristic_estimate(state, goals):
    min_dist = sum_dist(state.boxes, goals)
    # for boxes in itertools.permutations(state.boxes):
    #     for perm_goals in itertools.permutations(goals):
    #         temp = sum_dist(boxes, perm_goals)
    #         if (temp < min_dist):
    #             min_dist = temp
    return min_dist
    # return state.boxes_left

def get_step_path(initial_state, goals):
    h = []
    prev_state_map = {initial_state : (None,None)}
    heapq.heappush(h, (0, initial_state))
    gScore = {initial_state : 0}
    fScore = {initial_state : heuristic_estimate(initial_state, goals)}
    closedSet = set()

    while len(h) > 0:
        f, current = heapq.heappop(h)
        if current.is_solved():
            # print("checkpoint")
            return construct_path(prev_state_map, current)
        closedSet.add(current)
        neighbors = current.get_neighbours()
        # print("checkpoint1")
        for neighbor, dir in neighbors:
            # print(neighbors)
            if neighbor in closedSet:
                # global fail_cntr
                # print(fail_cntr)
                # fail_cntr += 1
                continue
            g = gScore[current] + 1
            if neighbor in gScore and g >= gScore[neighbor]:
                continue
            prev_state_map[neighbor] = (current, dir)
            gScore[neighbor] = g
            fScore[neighbor] = g + heuristic_estimate(neighbor, goals)
            heapq.heappush(h, (fScore[neighbor], neighbor))
    return []
def print_solution(step_path, ofile):
    for step in step_path:
        ofile.write(step)
    ofile.write("\n")

def main():
    with open("zad_input.txt") as ifile:
        with open("zad_output.txt", "w") as ofile:
            board = [list(line[:-1]) for line in ifile]
            player = (0,0)
            boxes = []
            boxes_left = 0
            goals = []
            for i in range(len(board)):
                for j in range(len(board[i])):
                    if board[i][j] == "K":
                        board[i][j] = "."
                        player = (i, j)
                    elif board[i][j] == "+":
                        board[i][j] = "G"
                        goals.append((i, j))
                        player = (i, j)
                    elif board[i][j] == "B":
                        board[i][j] = "."
                        boxes_left += 1
                        boxes.append((i, j))
                    elif board[i][j] == "*":
                        board[i][j] = "G"
                        goals.append((i, j))
                        boxes.append((i, j))
                    elif board[i][j] == "G":
                        goals.append((i, j))
            # print(player)
            # print(boxes)
            # print(board)
            # print(boxes_left)
            initial_state = State(player, boxes, board, boxes_left)
            step_path = get_step_path(initial_state, goals)
            # print(step_path)
            print_solution(step_path, ofile)

if __name__ == '__main__':
    main()
