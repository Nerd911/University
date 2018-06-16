from sys import argv
def is_check(w_king, w_rook, b_king):
    temp = diff_moves(w_king, b_king)
    if abs(temp[0]) <= 1 or abs(temp[1]) <= 1:
        return True
    temp = diff_moves(w_rook, w_king)
    temp1 = diff_moves(w_rook, b_king)
    return (w_rook[0] == b_king[0] and (temp[0] != 0 or temp[1] > temp1[1])) or (w_rook[1] == b_king[1] and (temp[1] != 0 or temp[0] > temp1[0]))

def diff_moves(pos1, pos2):
    return [pos1[0] - pos2[0], pos1[1] - pos2[1]]

def sum_moves(pos1, pos2):
    return [pos1[0] + pos2[0], pos1[1] + pos2[1]]
checked = [[[[False]*2]*64]*64]*64
def count_moves(w_king, w_rook, b_king, turn, debug_mode):
    w_king_index = w_king[0] * 8 + w_king[1]
    w_rook_index = w_rook[0] * 8 + w_rook[1]
    b_king_index = b_king[0] * 8 + b_king[1]
    print(w_king_index)
    print(w_rook_index)
    print(b_king_index)
    # print(int(turn))
    # print(checked)
    if(checked[w_king_index][w_rook_index][b_king_index][int(turn)]):
        return -1
    checked[w_king_index][w_rook_index][b_king_index][int(turn)] = True
    moves = -1
    if turn:
        for x in [-1, 0, 1]:
            for y in [-1, 0, 1]:
                # if x == 0 and y == 0:
                #     continue
                pos = sum_moves(b_king, [x, y])
                if is_check(w_king, w_rook, pos):
                    continue
                cnt = count_moves(w_king, w_rook, pos, not turn, debug_mode) + 1
                if(cnt == 0):
                    continue
                moves = cnt if moves == -1 or moves > cnt else moves
        return moves if moves != -1 else 0
    dif = diff_moves(b_king, w_rook)
    pos = sum_moves(w_rook, (dif[0],0))
    # if is_check(w_king, pos, b_king):
    #     return 1
    cnt = count_moves(w_king, pos, b_king, not turn, debug_mode) + 1
    if(cnt != 0):
        moves = cnt if moves == -1 or moves > cnt else moves
    pos = sum_moves(w_rook, (0,dif[1]))
    # if is_check(w_king, pos, b_king):
    #     return 1
    cnt = count_moves(w_king, pos, b_king, not turn, debug_mode) + 1
    if(cnt != 0):
        moves = cnt if moves == -1 or moves > cnt else moves
    for x in [-1, 0, 1]:
        for y in [-1, 0, 1]:
            if x == 0 and y == 0:
                continue
            pos = sum_moves(w_king, [x, y])
            # if is_check(pos, w_rook, b_king):
            #     return 1
            cnt = count_moves(pos, w_rook, b_king, not turn, debug_mode) + 1
            if(cnt == 0):
                continue
            moves = cnt if moves == -1 or moves > cnt else moves

def process_line(line, debug_mode):
    # print(line)
    turn, w_king, w_rook, b_king = line.split(" ")
    turn = turn == "black"
    convert = lambda s: [ord(s[0]) - ord('a'), ord(s[1]) - ord('1')]
    w_king = convert(w_king)
    w_rook = convert(w_rook)
    b_king = convert(b_king)
    # print(turn)
    # print(w_king)
    # print(w_rook)
    # print(b_king)
    moves = count_moves(w_king, w_rook, b_king, turn, debug_mode)
    return moves

def main():
    filename = ""
    if len(argv) == 1 or len(argv) == 2 and argv[1] == "debug":
        filename = input("Podaj nazwe pliku")
    elif len(argv) == 2 or len(argv) == 3 and argv[1] == "debug":
        filename = argv[1] if len(argv) == 2 else argv[2]
    else:
        return
    debug_mode = len(argv) > 1 and argv[1] == "debug"
    with open(filename) as file:
        for line in file:
            print(process_line(line[:-1], debug_mode))

if __name__ == '__main__':
    main()
