def evaluate_score(window, query):
    score = 0
    for i in range(0, len(query)):
        char_score = 3 if window[i] == query[i].encode("ascii") else -3
        score += char_score
    return score

data_file = open('./Data/data.txt', 'rb')
match_file = open('./Data/match.txt', "w")

query = list("CACCA")

moving_window = []
cumsums = []

while 1:

    char = data_file.read(1)
    if not char:
        break

    if len(moving_window) != len(query):
        moving_window.append(char)
        if len(moving_window) == len(query):
            cumsums.append(evaluate_score(moving_window, query))
        continue

    moving_window.pop(0)
    moving_window.append(char)
    if len(cumsums) != 3:
        cumsums.append(evaluate_score(moving_window, query) + cumsums[-1])
        continue

    cumsums.pop(0)
    cumsums.append(evaluate_score(moving_window, query) + cumsums[-1])

    if cumsums[0] < cumsums[1] and cumsums[2] < cumsums[1]:
        cur_pos = data_file.tell()
        data_file.seek(-(len(query) + 1), 1)
        last_chars = data_file.read(len(query))
        last_window = [elem.encode("ascii") for elem in list(last_chars.decode("ascii"))]
        match_file.write(str(cur_pos) + "\t" + str(cumsums[1]) + "\t" + str(last_chars) + "\t" + str(evaluate_score(last_window, query)) + "\n")
        cumsums = [cumsums[-1]]
        data_file.seek(cur_pos)

data_file.close()
match_file.close()

# All matches have a score of at least +3 => the algorithm finds all strings with the same length as the query where at least half of the characters + 1 are correct.