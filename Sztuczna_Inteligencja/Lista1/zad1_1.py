from sys import argv
def is_check(w_king, w_rook, b_king):
    temp = diff_moves(w_king, b_king)
    if abs(temp[0]) <= 1 or abs(temp[1]) <= 1:
        return True
    temp = diff_moves(w_rook, w_king)
    temp1 = diff_moves(w_rook, b_king)
    return (w_rook[0] == b_king[0] and (temp[0] != 0 or temp[1] > temp1[1])) or (w_rook[1] == b_king[1] and (temp[1] != 0 or temp[0] > temp1[0]))

def is_mate(w_king, w_rook, b_king):
    for i in [-1, 0, 1]:
        for j in [-1, 0, 1]:
            if i == 0 and j == 0:
                continue
            pos = sum_moves(b_king, [i, j])
            if pos[0] < 0 or pos[1] < 0 or pos[0] >= 8 or pos[1] >= 8:
                continue
            if not is_check(w_king, w_rook, pos):
                return False
    return True
def to_index(pos):
    return pos[0]*8 + pos[1]

def to_pos(index):
    return [index/8, index % 8]
def generate_boards(debug = False):
    qu = Queue()
    for i in range(64):
        for j in range(64):
            for k in range(64):
                if i == j or j == k or k == i:
                    continue
                    w_king = to_pos(i)
                    w_rook = to_pos(j)
                    b_king = to_pos(k)
                    if is_mate(w_king, w_rook, b_king):
                        counts[i][j][k][0] = counts[i][j][k][1] = 0
                        qu.put((i, j, k, 0))
    while not qu.empty():
        wk, wr, bk, turn = qu.get()
        w_king = to_pos(wk)
        w_rook = to_pos(wr)
        b_king = to_pos(bk)
        if turn == 1:
            for i in [-1, 0, 1]:
                for j in [-1, 0, 1]:
                    if i == j:
                        continue
                    pos = sum_moves(b_king, [i, j])
                    index = to_index(pos)
                    if index == wk or index == wr:
                        continue
                    if counts[wk][rk][pos][0] != -1:
                        continue
                    counts[wk][rk][pos][0] = counts[wk][rk][bk][turn] + 1
                    qu.put((wk, rk, pos, 0))
                    if (debug):
                        moves[wk][rk][pos][0] = (wk, wr, bk, turn)
            continue

        for i in [-1, 0, 1]:
            for j in [-1, 0, 1]:
                if i == j:
                    continue
                pos = sum_moves(b_king, [i, j])
                index = to_index(pos)
                if index == bk or index == wr:
                    continue
                if counts[pos][rk][bk][1] != -1:
                    continue
                counts[pos][rk][nk][1] = counts[wk][rk][bk][turn] + 1
                qu.put((pos, rk, bk, 1))
                if (debug):
                    moves[wk][rk][pos][0] = (wk, wr, bk, turn)

        begin = 0
        end = 8
        if w_king[0] == w_rook[0]:
            if w_king[1] < w_rook[1]:
                begin = w_king[1] + 1
            else:
                end = w_king[1]
        for i in range(begin, end):
            if i == w_rook[1]:
                continue
            pos = [w_rook[0], i]


def diff_moves(pos1, pos2):
    return [pos1[0] - pos2[0], pos1[1] - pos2[1]]

def sum_moves(pos1, pos2):
    return [pos1[0] + pos2[0], pos1[1] + pos2[1]]

counts = [[[[-1]*2]*64]*64]*64
moves = [[[[-1]*2]*64]*64]*64
