from cs50 import get_int

# GET CREDIT CARD NUMBER FROM USER
c_num = get_int("Enter your credit card number: ")


# DRIVER AND CLASSIFIER FUNCTION
def main():
    num = str(c_num)
    if get_sum(c_num) % 10 != 0:
        print("INVALID")

    elif len(num) == 15 and int(num[0]) == 3 and (int(num[1]) == 4 or int(num[1]) == 7):
        print("AMEX")

    elif int(num[0]) == 4 and (len(num) == 13 or len(num) == 16):
        print("VISA")

    elif len(num) == 16 and int(num[0]) == 5 and (int(num[1]) in [1, 2, 3, 4, 5]):
        print("MASTERCARD")


# SPLIT AND ADD DIGITS
def split(num):

    L = []
    if num > 9:
        L.append(num % 10)
        L.append(num // 10)
        return L[0] + L[1]
    return num


# SUM APPROPRIATE CARD NUMBER DIGITS
def get_sum(c_num):

    L_even = []
    L_odd = []
    for i in range(len(str(c_num))):
        if i % 2 == 0:
            temp = c_num % 10
            L_even.append(split(temp))
            c_num = c_num // 10
        else:
            temp = c_num % 10
            L_odd.append(split(2*temp))
            c_num = c_num // 10
    return sum(L_odd) + sum(L_even)


# NAMEGAUARD
if __name__ == "__main__":

    main()
