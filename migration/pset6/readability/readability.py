# user doniyor on stackoverflow provided this solution on 11.18.14
# as a means to check if a char is whitespace
def space_check(c):
    if ' ' in c:
        return True
        

# receive input from user
text = input("Text: ")
# convert text to uppercase
text = text.upper()

letters = 0
words = 1
sentences = 0

for i in range(0, len(text)):
    # compare chars at i to ASCII value between A-Z
    if ord(text[i]) >= 65 and ord(text[i]) <= 90:
        letters += 1
    # using space_check to check whitespace
    if space_check(text[i]):
        words += 1
    # compare chars at i to ASCII values of punctuation
    if ord(text[i]) == 33 or ord(text[i]) == 46 or ord(text[i]) == 63:
        sentences += 1

# Coleman-Liau index
L = float(letters / words) * 100
S = float(sentences / words) * 100
index = round(0.0588 * L - 0.296 * S - 15.8)

if index < 1:
    print("Before Grade 1")
elif index > 16:
    print("Grade 16+")
else:
    print(f"Grade {index}")