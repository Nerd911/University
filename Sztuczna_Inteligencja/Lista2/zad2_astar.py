import heapq
import itertools
class State:
    def __init__(self, player, boxes, board, boxes_left, goals):
        self.player = player
        self.boxes = boxes
        self.board = board
        self.boxes_left = boxes_left
        self.height = len(board)
        self.width = len(board[0])
        self.goals = goals
        # self.min_box_dist = self.__closest_box_dist()
        self.min_box_dist_sum = -1
        # self.print_state()
    def __closest_box_dist(self):
        result = dist(self.player, self.boxes[0])
        l = len(self.boxes)
        for i in range(1, l):
            temp = dist(self.player, self.boxes[i])
            if temp < result:
                result = temp
        return result

    def get_min_box_dist_sum(self):
        if self.min_box_dist_sum == -1:
            self.min_box_dist_sum = self.heuristic_estimate()
        return self.min_box_dist_sum

    def heuristic_estimate(self):
        # min_dist = sum_dist(self.boxes, self.goals)
        # for boxes in itertools.permutations(self.boxes):
        #     for perm_goals in itertools.permutations(self.goals):
        #         temp = sum_dist(boxes, perm_goals)
        #         if (temp < min_dist):
        #             min_dist = temp
        # free_goals = set(self.goals) - set(self.boxes)
        # min_dist = dist(self.boxes[0], self.goals[0])
        # for box in self.boxes:
        #     for goal in free_goals:
        #         temp = dist(box, goal)
        #         if temp != 0 and temp < min_dist:
        #             min_dist = temp
        # return min_dist
        return self.boxes_left

    def print_board(self):
        for row in self.board:
            for col in row:
                print(col, end = "")
            print("")
    def print_state(self):
        print("Player: {}".format(self.player))
        print("Boxes: {}".format(self.boxes))
        print("Boxes left: {}".format(self.boxes_left))
        self.print_board()
    def get_repr(self):
        return (self.player, tuple(self.boxes))

    def __hash__(self):
        return hash(self.get_repr())

    def __eq__(self, other):
        if isinstance(other, State):
            return self.get_repr() == other.get_repr()
        return False

    def is_solved(self):
        return self.boxes_left == 0

    def is_push_valid(self, pos, dir):
        new_pos = add_pos(pos, dir)
        if new_pos[0] < 0 or new_pos[1] < 0 or new_pos[0] >= self.height or new_pos[1] >= self.width:
            return False
        if new_pos in self.boxes:
            return False
        return self.board[new_pos[0]][new_pos[1]] != 'W'

    def is_move_valid(self, dir):
        new_pos = add_pos(self.player, dir)
        if new_pos[0] < 0 or new_pos[1] < 0 or new_pos[0] >= self.height or new_pos[1] >= self.width:
            return False
        if new_pos in self.boxes:
            return self.is_push_valid(new_pos, dir)
        return self.board[new_pos[0]][new_pos[1]] != 'W'

    def generate_state(self, dir):
        # print("self.player: {}".format(self.player))
        # print("dir: {}".format(dir))
        new_pos = add_pos(self.player, dir)
        # print("new_pos: {}".format(new_pos))
        if new_pos in self.boxes:
            # print("pushed")
            boxes = self.boxes[:]
            box_pos = add_pos(new_pos, dir)
            boxes[boxes.index(new_pos)] = box_pos
            boxes_left = self.boxes_left - int(self.board[box_pos[0]][box_pos[1]] == 'G') + int(self.board[new_pos[0]][new_pos[1]] == 'G')
            return State(new_pos, boxes, self.board, boxes_left, self.goals)
        return State(new_pos, self.boxes, self.board, self.boxes_left, self.goals)

    def get_neighbours(self):
        neighbors = []
        for dir in [(-1, 0), (1, 0), (0, 1), (0, -1)]:
            # print(dir)
            if self.is_move_valid(dir):
                new_state = self.generate_state(dir)
                neighbors.append(new_state)
            # else:
            #     print("Player: {} Boxes: {} Dir: {}".format(self.player, self.boxes, dir))
        return neighbors

    def __lt__(self, other):
        return self.get_min_box_dist_sum() < other.get_min_box_dist_sum()


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
        cur_state = prev_state_map[cur_state]
        if cur_state is not None:
            path.append(directions_dict[diff_pos(temp.player, cur_state.player)])
    return list(reversed(path))

def dist(pos0, pos1):
    return abs(pos0[0] - pos1[0]) + abs(pos0[1] - pos1[1])

def sum_dist(positions0, positions1):
    l = len(positions0)
    return sum([dist(positions0[i], positions1[i]) for i in range(l)])

def get_step_path(initial_state):
    h = []
    prev_state_map = {initial_state : None}
    heapq.heappush(h, (0, initial_state))
    gScore = {initial_state : 0}
    fScore = {initial_state : initial_state.get_min_box_dist_sum()}
    closedSet = set()

    while len(h) > 0:
        f, current = heapq.heappop(h)
        if current.is_solved():
            return construct_path(prev_state_map, current)
        closedSet.add(current)
        neighbors = current.get_neighbours()
        for neighbor in neighbors:
            if neighbor in closedSet:
                continue
            g = gScore[current] + 1
            if neighbor in gScore and g >= gScore[neighbor]:
                continue
            prev_state_map[neighbor] = current
            gScore[neighbor] = g
            fScore[neighbor] = g + neighbor.get_min_box_dist_sum()
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
            initial_state = State(player, boxes, board, boxes_left, goals)
            step_path = get_step_path(initial_state)
            # print(step_path)
            print_solution(step_path, ofile)

if __name__ == '__main__':
    main()
