import random
dic = dict()
with open("words_for_ai1.txt") as f:
    for line in f:
        dic[line[:-1]] = len(line)**2

def get_spacing(text):
    l = len(text)
    words = []
    for i in range(1, l+1):
        word = text[0:i]
        if word in dic:
            words.append((word, i))
    random.shuffle(words)
    for word, i in words:
        if i == l:
            return word + "\n"
        suffix = get_spacing(text[i:])
        if suffix != "":
            return word + " " + suffix
    return ""
with open("zad4_input.txt") as ifile:
    with open("zad4_output.txt", "w") as ofile:
        for line in ifile:
            text = line[:-1]
            result = get_spacing(text)
            ofile.write(result)
