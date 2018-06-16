from collections import deque

class Board:
    def __init__(self, w_king, w_rook, b_king, player_turn):
        self.w_king = w_king
        self.w_rook = w_rook
        self.b_king = b_king
        self.player_turn = player_turn

    def get_opponent_player(self):
        return 1 - self.player_turn

    def get_moved_field(self, field, direction):
        return (field[0] + direction[0], field[1] + direction[1])

    def is_field_valid(self, field):
        return (field[0] >= 0 and field[0] <= 7 and field[1] >= 0 and field[1] <= 7)

    def is_field_empty(self, field):
        return (field not in [self.w_king, self.w_rook, self.b_king])

    def get_repr(self):
        return (self.w_king, self.w_rook, self.b_king, self.player_turn)

    def __hash__(self):
        return hash(self.get_repr())

    def __eq__(self, other):
        if isinstance(other, Board):
            return self.get_repr() == other.get_repr()
        return False

    def get_w_rook_direct_neighbors(self, direction):
        neighbors = []
        for move_size in range(1, 8):
            move_pos = (direction[0] * move_size, direction[1] * move_size)
            rook_pos = self.get_moved_field(self.w_rook, move_pos)
            if not self.is_field_valid(rook_pos) or not self.is_field_empty(rook_pos):
                break
            if self.is_beaten_by_king(rook_pos, self.b_king):
                continue
            neighbors.append(Board(self.w_king, rook_pos, self.b_king, self.get_opponent_player()))
        return neighbors

    def get_w_rook_neighbors(self):
        neigh_func = (lambda x: self.get_w_rook_direct_neighbors(x))
        return neigh_func((1, 0)) + neigh_func((-1, 0)) + neigh_func((0, 1)) + neigh_func((0, -1))

    def is_beaten_by_king(self, pos, king_pos):
        dist_x = abs(pos[0] - king_pos[0])
        dist_y = abs(pos[1] - king_pos[1])
        return (dist_x <= 1 and dist_y <= 1)

    def is_move_valid(self, king_pos, opp_king_pos, banned_x=None, banned_y=None):
        if self.is_field_valid(king_pos) == False or self.is_field_empty(king_pos) == False:
            return False
        if king_pos[0] == banned_x or king_pos[1] == banned_y:
            return False
        return not self.is_beaten_by_king(king_pos, opp_king_pos)

    def get_w_king_neighbors(self):
        neighbors = []
        for dir_x in range(-1,2):
            for dir_y in range(-1,2):
                if dir_x == 0 and dir_y == 0:
                    continue
                king_pos = self.get_moved_field(self.w_king, (dir_x, dir_y))
                if self.is_move_valid(king_pos, self.b_king) and not self.is_beaten_by_king(self.w_rook, self.b_king):
                    neighbors.append(Board(king_pos, self.w_rook, self.b_king, self.get_opponent_player()))
        return neighbors

    def get_b_king_neighbors(self):
        neighbors = []
        for dir_x in range(-1,2):
            for dir_y in range(-1,2):
                if dir_x == 0 and dir_y == 0:
                    continue
                king_pos = self.get_moved_field(self.b_king, (dir_x, dir_y))
                if self.is_move_valid(king_pos, self.w_king, self.w_rook[0], self.w_rook[1]):
                    neighbors.append(Board(self.w_king, self.w_rook, king_pos, self.get_opponent_player()))
        return neighbors

    def get_neighbours(self):
        if self.player_turn == 0:
            return self.get_w_king_neighbors() + self.get_w_rook_neighbors()
        else:
            return self.get_b_king_neighbors()

def encode_position(pos_str):
    return (ord(pos_str[0]) - ord('a'), int(pos_str[1]) - 1)

def decode_position(pos):
    return chr(ord('a') + pos[0]) + str(pos[1] + 1)

def encode_player(player_str):
    return {'white': 0, 'black': 1}[player_str]

def decode_player(player):
    return ['white', 'black'][player]

def construct_path(prev_state_map, cur_state):
    path = []
    while cur_state is not None:
        path.append(cur_state)
        cur_state = prev_state_map[cur_state]
    return list(reversed(path))

def get_step_path(initial_board):
    boards_queue = deque([initial_board])
    prev_board_map = {initial_board: None}
    while len(boards_queue) > 0:
        cur_state = boards_queue.popleft()
        neighbors = cur_state.get_neighbours()
        if len(neighbors) == 0:
            return construct_path(prev_board_map, cur_state)
        for neighbor in neighbors:
            if neighbor not in prev_board_map:
                prev_board_map[neighbor] = cur_state
                boards_queue.append(neighbor)
    return []

def create_board(line):
    splitted_line = line.split()
    w_king, w_rook, b_king = [encode_position(x) for x in splitted_line[1:]]
    player_turn = encode_player(splitted_line[0])
    return Board(w_king, w_rook, b_king, player_turn)

def main():
    with open("zad1_input.txt") as ifile:
        with open("zad1_output.txt", "w") as ofile:
            for line in ifile:
                board = create_board(line)
                ofile.write("{}\n".format(len(get_step_path(board)) - 1))

if __name__ == "__main__":
    main()
