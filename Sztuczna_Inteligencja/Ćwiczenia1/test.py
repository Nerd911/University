lines = []
with open("good.txt") as f:
    lines = [line for line in f]
l = len(lines)
cntr = 0
with open("zad2_output.txt") as f:
    i = 0
    for line in f:
        if line == lines[i]:
            cntr += 1
        i+=1
    print(cntr/l)
cntr = 0
with open("zad4_output.txt") as f:
    i = 0
    for line in f:
        if line == lines[i]:
            cntr += 1
        i+=1
    print(cntr/l)
