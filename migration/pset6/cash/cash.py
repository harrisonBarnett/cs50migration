# while True, try/except to emulate do/while
while True:
    try:
        change = float(input("Change owed: "))
    except ValueError:
        continue
    if change >= 0:
        break
    
cents = int(round(change * 100))

counter = 0
while cents > 0:
    # while the number >= 25, decrease by 25 until it is < 25
    # then try the next denomination, and so on
    if cents >= 25:
        while cents >= 25:
            cents -= 25
            counter += 1
    elif cents >= 10:
        while cents >= 10:
            cents -= 10
            counter += 1
    elif cents >= 5:
        while cents >= 5:
            cents -= 5
            counter += 1
    elif cents >= 1:
        while cents >= 1:
            cents -= 1
            counter += 1

print(counter)
    