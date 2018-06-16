import sys


def V(i,j):
    return 'V%d_%d' % (i,j)

def domains(Vs):
    return [ q + ' in 1..9' for q in Vs ]

def all_different(Qs):
    return 'all_distinct([' + ', '.join(Qs) + '])'

def get_column(j):
    return [V(i,j) for i in range(9)]

def get_raw(i):
    return [V(i,j) for j in range(9)]

def get_square(i, j):
	px, py = i * 3, j * 3
	return [ V(px + ox, py + oy) for ox in range(3) for oy in range(3) ]

def horizontal():
    return [ all_different(get_raw(i)) for i in range(9)]

def vertical():
    return [all_different(get_column(j)) for j in range(9)]

def area():
	return [ all_different(get_square(i, j)) for i in range(3) for j in range(3) ]

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

def sudoku(assigments):
    variables = [ V(i,j) for i in range(9) for j in range(9)]

    print ':- use_module(library(clpfd)).'
    print 'solve([' + ', '.join(variables) + ']) :- '


    cs = domains(variables) + vertical() + horizontal() + area()
    for i,j,val in assigments:
        cs.append( '%s #= %d' % (V(i,j), val) )

    print_constraints(cs, 4, 70),
    print
    print '    labeling([ff], [' +  ', '.join(variables) + ']).'
    print
    print ":- tell('prolog_result.txt'), solve(X), write(X), nl, told."

if __name__ == "__main__":
    triples = []
    with open('zad_input.txt', 'r') as input_file:
        input_lines = map(lambda x: list(x), input_file.readlines())
        for i in range(len(input_lines)):
            for j in range(9):
                if input_lines[i][j] != '.':
                    triples.append((i, j, int(input_lines[i][j])))
    sys.stdout = open('zad_output.txt', 'w')
    sudoku(triples)
