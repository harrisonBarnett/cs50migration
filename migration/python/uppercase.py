from cs50 import get_string

s = get_string("Before: ")
print("After: ", end="")
# iterate thru chars in a string
for c in s:
    print(c.upper(), end="")
print()