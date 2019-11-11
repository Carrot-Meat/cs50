from cs50 import get_int

height = 0
# CHECK FOR VALID INPUT
while height < 1 or height > 8:
    height = get_int("Enter desired height: ")

# CONSTRUCT PYRAMID OF HEIGHT = "height"
for i in range(1, height + 1):
    spaces = height - i
    print(f" "*(spaces), "#"*i, "  ", "#"*i, sep="")
