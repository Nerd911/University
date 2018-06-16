import sys

def V(i, j):
    return 'V%d_%d' % (i, j)

def domains(Vs):
    return [q + ' in 0..1' for q in Vs]

def all_different(Qs):
    return 'all_distinct([' + ', '.join(Qs) + '])'

def get_row(i):
    return [V(i, j) for j in range(len(cols))]

def get_column(j):
    return [V(i, j) for i in range(len(rows))]

def create_line(v_list, result):
    return ' + '.join(v_list) + ' #= ' + str(result)

def line_sum(rows, cols):
    row_sums = map(lambda x: create_line(get_row(x), rows[x]), range(len(rows)))
    col_sums = map(lambda x: create_line(get_column(x), cols[x]), range(len(cols)))
    return row_sums + col_sums

def get_neigh_x(i, j):
    return [V(i + offset, j) for offset in range(3)]

def get_neigh_y(i, j):
    return [V(i, j + offset) for offset in range(3)]

def create_neigh(val_list):
    return " #\\ {1} #= 1 #\\/ {0} #= 1 #\\/ {2} #= 1".format(*val_list)

def neigh_sum(rows, cols):
    neighs_x = [create_neigh(get_neigh_x(i, j)) for i in range(len(rows) - 2) for j in range(len(cols))]
    neighs_y = [create_neigh(get_neigh_y(i, j)) for i in range(len(rows)) for j in range(len(cols) - 2)]
    return neighs_x + neighs_y

def get_2x2_square(px, py):
    return [V(px + ox, py + oy) for ox in range(2) for oy in range(2)]

def create_2x2_square(v_list):
    one_rule_str = "{0} + {1} + {2} + {3} #= 1".format(*v_list)
    eq_rule_str = "{0} + {3} #= {1} + {2}".format(*v_list)
    return one_rule_str + " #\\/ " + eq_rule_str

def square_sum(rows, cols):
    return [create_2x2_square(get_2x2_square(i, j)) for i in range(len(rows)) for j in range(len(cols))]

def print_constraints(Cs, indent, d):
    position = indent
    print (indent - 1) * ' ',
    for c in Cs:
        print c + ',',
        position += len(c)
        if position > d:
            position = indent
            print
            print (indent - 1) * ' ',

def create_program(rows, cols, limits):
    var_names = [V(i, j) for i in range(len(rows)) for j in range(len(cols))]
    print ':- use_module(library(clpfd)).'
    print 'solve([' + ', '.join(var_names) + ']) :- '
    cs = domains(var_names)
    cs += line_sum(rows, cols)
    cs += neigh_sum(rows, cols)
    cs += square_sum(rows, cols)
    for i, j, val in limits:
        cs.append('%s #= %d' % (V(i, j), val))
    print_constraints(cs, 4, 70),
    print
    print '    labeling([ff], [' + ', '.join(var_names) + ']).'
    print
    print ":- tell('prolog_result.txt'), solve(X), write(X), nl, told."

if __name__ == "__main__":
    limits = []
    map_func = (lambda line: map(lambda x: int(x), ''.join(line).split()))
    with open('zad_input.txt', 'r') as input_file:
        input_lines = map(lambda x: list(x), input_file.readlines())
        rows = map_func(input_lines[0])
        cols = map_func(input_lines[1])
        for i in range(2, len(input_lines)):
            limits.append(tuple(map_func(input_lines[i])))
    sys.stdout = open('zad_output.txt', 'w')
    create_program(rows, cols, limits)
