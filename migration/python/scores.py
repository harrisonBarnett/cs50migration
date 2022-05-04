from cs50 import get_int

scores = []
for i in range(3):
    scores.append(get_int("Score: "))

print("Average: " + str(sum(scores) / len(scores)))