dic = dict()
with open("words_for_ai1.txt") as f:
    for line in f:
        dic[line[:-1]] = len(line)**2

with open("zad2_input.txt") as ifile:
    with open("zad2_output.txt", "w") as ofile:
        for line in ifile:
            text = line[:-1]
            l = len(text)
            sums = [0]*(l+1)
            indices = [0] * (l+1)
            for i in range(0, l):
                for j in range(i+1, l+1):
                    temp_text = text[i:j]
                    if temp_text in dic:
                        temp_sum = sums[i-1] + dic[temp_text]
                        if temp_sum > sums[j-1]:
                            # print(temp_text)
                            sums[j-1] = temp_sum
                            indices[j-1] = i
            # print(indices)
            # print(sums)
            result = []
            begin, end = indices[l-1], l
            while begin != 0:
                result.append(text[begin:end])
                end = begin
                begin = indices[begin-1]
            result.append(text[begin:end])
            ofile.write(" ".join(reversed(result)) + "\n")
