import random
from collections import deque
import copy
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
        self.rows_perm = [self.get_row_perms(row, self.nr_of_columns) for row in self.rows]
    def get_cols_left(self, column):
        result = deque()
        l = len(column)
        for i in range(l):
            result.append(column[i])
            if i != l -1:
                result.append(0)
        return result
    def __get_row_perms(self, counts, l):
        result = []
        count = counts[0]
        if l < count:
            return []
        if len(counts) == 1:
            return [[1] * count + [0] * (l-count)]
        s = sum(counts[1:])
        for i in range(count+1, l - s + 1):
            for perm in self.__get_row_perms(counts[1:], l - i):
                result.append([1]*count + [0]*(i-count) + perm)
        return result
    def get_row_perms(self, counts, l):
        result = []
        s = sum(counts)
        count = counts[0]
        for i in range(l - s + 1):
            for perm in self.__get_row_perms(counts, l - i):
                result.append([0]*i + perm)
        print(result)
        return result
    def __get_possible_cols_left(self, cols_sum, cols_left, perm):
        cols_cntrs = [(x[0] if len(x) > 0 else 0) for x in cols_left]
        # print(cols_cntrs)
        # print(cols_sum)
        # print(self.nr_of_columns)
        # print(len(cols_left))
        # print(len(self.columns))
        new_cols_left = copy.deepcopy(cols_left)
        temp = diff_rows(cols_cntrs, cols_sum)
        l = len(cols_sum)
        new_cols_sum = cols_sum[:]
        for i in range(l):
            if(temp[i] < 0 or (perm[i] == 0 and temp[i] != 0)):
                return (None, None)
            if(temp[i] == 0 and len(new_cols_left[i])>0):
                new_cols_left[i].popleft()
                # print("checkpoint popleft")
                new_cols_sum[i] = 0
        # print(new_cols_left)
        # print(new_cols_sum)
        return (new_cols_sum, new_cols_left)

    def dfs(self, row, solution, cols_sum, cols_count):
        # print(cols_left)
        if row == self.nr_of_rows:
            for i in range(self.nr_of_columns):
                if cols_sum[i] != 0:
                    cols_count[i].append(cols_sum[i])
                # print(cols_count)
                # print(self.columns)
                if cols_count[i] != self.columns[i]:
                    # print("Fail1")
                    return False
            # print("success")
            return True
        for perm in self.rows_perm[row]:
            solution[row] = perm
            # print(len(perm))
            new_sum = add_rows(cols_sum, perm)
            new_cols_count = copy.deepcopy(cols_count)
            for i in range(len(perm)):
                if(perm[i] == 0 and new_sum[i] != 0):
                    new_cols_count[i].append(new_sum[i])
                    new_sum[i] = 0
                    if (new_cols_count[i] != self.columns[i][:len(new_cols_count[i])]):
                        continue
            if self.dfs(row+1, solution, new_sum, new_cols_count):
                return True
        # print("Fail3")
        return False

    def solve(self):
        # print(self.cols_left)
        solution = [[0] * self.nr_of_columns for i in range(self.nr_of_rows)]
        self.dfs(0, solution, [0]*self.nr_of_columns, [[] for i in range(self.nr_of_columns)])
        self.solved = solution
        return solution

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

    def print_solution(self, ofile):
        for row in self.solved:
            for character in row:
                if character == 1:
                    ofile.write("#")
                else:
                    ofile.write(".")
            ofile.write("\n")

def count_in_columns(row1, row2):
    l = len(row1)
    result = row1[:]
    for i in range(l):
        result[i] = row1[i] + row2[i] if row2[i] > 0 else 0
    return result
def add_rows(row1, row2):
    l = len(row1)
    result = row1[:]
    for i in range(l):
        result[i] += row2[i]
    return result

def diff_rows(row1, row2):
    l = len(row1)
    result = row1[:]
    for i in range(l):
        result[i] -= row2[i]
    return result

def main():
    with open("zad_input.txt") as ifile:
        with open("zad_output.txt", "w") as ofile:
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
                    picture[0].append([int(word) for word in line.split(" ")])
                    cntr += 1
                    continue
                picture[1].append([int(word) for word in line.split(" ")])
                if cntr == rows + cols:
                    cntr = 0
                    pic = Picture(picture, rows, cols)
                    pic.solve()
                    pic.print_solution(ofile)
                    continue
                cntr += 1

if __name__ == "__main__":
    main()
