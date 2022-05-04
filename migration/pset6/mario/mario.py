# simulating a do-while to make sure input is greater than 0
# and does not exceed 8

while True:
    # try/except allows us to filter inputs based on whether
    # or not they are an int
    try:
        height = int(input("Height: "))
    except ValueError:
        continue
    if height >= 1 and height <= 8:
        break

for i in range(0, height):
    for j in range(0, height - 1 - i):
        # prints height - 1 spaces
        print(" ", end="")
    for j in range(0, i + 1):
        # prints i number of blocks
        print("#", end="")
        # prints space between pyramids
    print("  ", end="")
    
    # iterates through and prints the mirror of above
    for j in range(0, i + 1):
        print("#", end="")
    print()
            