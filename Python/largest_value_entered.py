# Michael Coughlin
# hiimmichael.com
# 2019

__author__ = 'Michael'

print("Enter 0 or any negative number to exit.\n")
largest = 0
temp = 0
condition = True

while condition:
    temp = int(input("Please enter an integer: "))
    if temp > largest:
        largest = temp
    elif temp <= 0:
        condition = False

print("The largest value that was entered is: " + str(largest))

