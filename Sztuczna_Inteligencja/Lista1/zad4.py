import random
def opt_dist(li, D):
    result = 0
    l = len(li)
    for i in range(0, D):
        result += int(li[i] != 1)
    for i in range(D, l):
        result += int(li[i] != 0)
    cntr = result
    for i in range(D, l):
        cntr = cntr - int(li[i] == 1) + int(li[i] == 0) - int(li[i-D] == 0) + int(li[i-D] == 1)
        if cntr < result:
            result = cntr
    return result


class Picture:
    def __init__(self, picture, nr_of_rows = 7, nr_of_columns = 7):
        self.rows = picture[0]
        self.columns = picture[1]
        self.nr_of_rows = nr_of_rows
        self.nr_of_columns = nr_of_columns

    def _is_solved(self, cntr):
        for elem in cntr:
            if elem != 0:
                return False
        return True

    def _get_dist(self, i, j):
        self.solved[i][j] = 1 - self.solved[i][j]
        # print(1)
        # self.print()
        row_dist = opt_dist(self.solved[i], self.rows[i])
        col_dist = opt_dist([row[j] for row in self.solved], self.columns[j])
        # print(self.solved[:][j])
        # print("columns[j]: {}".format(self.columns[j]))
        self.solved[i][j] = 1 - self.solved[i][j]
        # print(2)
        # self.print()
        return (row_dist, col_dist)

    def _solve(self, is_row):
        n = self.nr_of_rows if is_row else self.nr_of_columns
        i = random.randint(0, n-1)
        if is_row:
            # print("checkpoint 0")
            while(self.row_cntr[i] == 0):
                i += 1
                i %= n
            # print("checkpoint 1")
            best_index = 0
            row_dist, col_dist = self._get_dist(i, 0)
            for j in range(1, self.nr_of_columns):
                temp_row, temp_col = self._get_dist(i, j)
                if temp_row**2 + temp_col**2 < row_dist**2 + col_dist**2:
                    best_index = j
                    row_dist, col_dist = temp_row, temp_col
            self.solved[i][best_index] = 1 - self.solved[i][best_index]
            # print("row_dist: {}".format(row_dist))
            self.row_cntr[i] = row_dist
            # print("col_dist: {}".format(col_dist))
            # print("({},{})".format(i, best_index))
            self.column_cntr[best_index] = col_dist

            return
        # print("checkpoint 2")
        while(self.column_cntr[i] == 0):
            i += 1
            i %= n
        # print("checkpoint 3")
        best_index = 0
        row_dist, col_dist = self._get_dist(0, i)
        for j in range(1, self.nr_of_rows):
            temp_row, temp_col = self._get_dist(j, i)
            if temp_row + temp_col < row_dist + col_dist:
                best_index = j
                row_dist, col_dist = temp_row, temp_col
        self.solved[best_index][i] = 1 - self.solved[best_index][i]
        # print("row_dist: {}".format(row_dist))
        # print("col_dist: {}".format(col_dist))
        # print("({},{})".format(best_index,i))
        self.row_cntr[best_index] = row_dist
        self.column_cntr[i] = col_dist

    def _init_solving(self):
        self.solved = [ [random.randint(0,1) for i in range(self.nr_of_columns)] for j in range(self.nr_of_rows)]
        self.row_cntr = [opt_dist(self.solved[i], self.rows[i]) for i in range(self.nr_of_rows)]
        self.column_cntr = [opt_dist([row[i] for row in self.solved], self.columns[i]) for i in range(self.nr_of_columns)]

    def solve(self):
        LIMIT = 100
        cntr = LIMIT
        rows_solved = cols_solved = False
        while not rows_solved or not cols_solved:
            if cntr == LIMIT:
                self._init_solving()
                rows_solved = self._is_solved(self.row_cntr)
                cols_solved = self._is_solved(self.column_cntr)
                cntr = 0
            if not rows_solved:
                # print("Row:")
                self._solve(True)
                rows_solved = self._is_solved(self.row_cntr)
                cols_solved = self._is_solved(self.column_cntr)
                # print("row_cntr: {}".format(self.row_cntr))
                # print("column_cntr: {}".format(self.column_cntr))
                # self.print_solution()
            if not cols_solved:
                # print("Column:")
                self._solve(False)
                rows_solved = self._is_solved(self.row_cntr)
                cols_solved = self._is_solved(self.column_cntr)
                # print("row_cntr: {}".format(self.row_cntr))
                # print("column_cntr: {}".format(self.column_cntr))
                # self.print_solution()
            # print(self.column_cntr)
            # print(self.row_cntr)

    def print_solution(self, ofile):
        for row in self.solved:
            for character in row:
                if character == 1:
                    ofile.write("#")
                else:
                    ofile.write(".")
            ofile.write("\n")

#
# with open("zad4_input.txt") as ifile:
#     with open("zad4_output.txt", "w") as ofile:
#         for line in ifile:
#             sequence, count = line[:-1].split(" ")
#             count = int(count)
#             sequence = [int(c) for c in sequence]
#             ofile.write("{}\n".format(opt_dist(sequence, count)))

def main():
    with open("zad5_input.txt") as ifile:
        with open("zad5_output.txt", "w") as ofile:
            cntr = 0
            cols = 0
            rows = 0
            picture = ([],[])
            for line in ifile:
                if cntr == 0:
                    splt = line.split(" ")
                    rows = int(splt[0])
                    cols = int(splt[1])
                    picture = ([], [])
                    cntr += 1
                    continue
                if cntr > 0 and cntr <= rows:
                    picture[0].append(int(line))
                    cntr += 1
                    continue
                picture[1].append(int(line))
                if cntr == rows + cols:
                    cntr = 0
                    pic = Picture(picture)
                    pic.solve()
                    pic.print_solution(ofile)
                    continue
                cntr += 1

if __name__ == "__main__":
    main()
