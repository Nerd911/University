from collections import deque
class State:
    def __init__(self, player, boxes, board, boxes_left):
        self.player = player
        self.boxes = boxes
        self.board = board
        self.boxes_left = boxes_left
        self.height = len(board)
        self.width = len(board[0])
        # self.print_state()
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
            return State(new_pos, boxes, self.board, boxes_left)
        return State(new_pos, self.boxes, self.board, self.boxes_left)

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

def get_step_path(initial_state):
    states_queue = deque([initial_state])
    prev_state_map = {initial_state: None}
    while len(states_queue) > 0:
        cur_state = states_queue.popleft()
        # cur_state.print_state()
        if cur_state.is_solved():
            return construct_path(prev_state_map, cur_state)
        neighbors = cur_state.get_neighbours()
        for neighbor in neighbors:
            # neighbor.print_state()
            if neighbor not in prev_state_map:
                # print("added state")
                prev_state_map[neighbor] = cur_state
                states_queue.append(neighbor)
    # print("checkpoint 1")
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
            for i in range(len(board)):
                for j in range(len(board[i])):
                    if board[i][j] == "K":
                        board[i][j] = "."
                        player = (i, j)
                    elif board[i][j] == "+":
                        board[i][j] = "G"
                        player = (i, j)
                    elif board[i][j] == "B":
                        board[i][j] = "."
                        boxes_left += 1
                        boxes.append((i, j))
                    elif board[i][j] == "*":
                        board[i][j] = "G"
                        boxes.append((i, j))
            initial_state = State(player, boxes, board, boxes_left)
            step_path = get_step_path(initial_state)
            # print(step_path)
            print_solution(step_path, ofile)

if __name__ == '__main__':
    main()
