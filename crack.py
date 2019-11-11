import sys
import crypt


# USEFUL CONSTS
ALPHABET = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ"
LEN = len(ALPHABET)
SIZE = LEN**5


# DRIVER
def main():
    pword = sys.argv[1]
    salt = f"{sys.argv[1][0:2]}"
    crack(pword, salt)


# BRUTE FORCE BY GENERATING STRINGS
def crack(pword, salt):

    count = 0
    for i in range(SIZE):
        temp = count
        temp1 = count
        chars = 0
        L = [0]*5
        # FIND NUMBER OF DIGITS BASE LEN
        while temp1 > LEN:
            temp1 = temp1 / LEN
            chars += 1
        # CONSTRUCT STRINGS BASE LEN
        while temp > 0:
            for j in range(chars, -1, -1):
                L[j] = ALPHABET[temp % LEN]
                temp = temp // LEN
        X = "".join(str(x) for x in L[0:chars+1])
        if pword == crypt.crypt(X, salt):
            print(X)
            return True
        count += 1
        print(X)


# NAMEGUARD
if __name__ == "__main__":
    main()
