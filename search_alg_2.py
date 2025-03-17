def evaluate_score(window, query):
    score = 0
    for i in range(0, len(query)):
        char_score = 3 if window[i] == query[i].encode("ascii") else -3
        score += char_score
    return score

data_file = open('./Data/data.txt', 'rb')
match_file = open('./Data/match_2.txt', "w")

query = list("CACCA")

moving_window = []
cumsums = []

while 1:

    chars = data_file.read(len(query))
    if len(chars) != len(query):
        break

    window = [elem.encode("ascii") for elem in list(chars.decode("ascii"))]
    score = evaluate_score(window, query)
    if score >= 3:
        cur_pos = data_file.tell()
        match_file.write(str(cur_pos) + "\t" + str(chars) + "\t" + str(score) + "\n")

    data_file.seek(-4, 1)

data_file.close()
match_file.close()

# The algorithm finds way more matches the alg. 1