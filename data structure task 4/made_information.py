import string
import random


class Student():
    def __init__(self, number, name, address):
        self.number = number
        self.name = name
        self.address = address


f = open("student_information.txt", 'w', encoding="utf8")

student_list = []
letters = string.ascii_letters
digits = ['0', '1', '2', '3', '4', '5', '6', '7', '8', '9']
check_wrap = []
for i in range(8):
    for j in range(2500):
        random_list = random.sample(digits, 4)  # storing number
        number = ''.join(random_list)
        number = str(2016 + i) + number
        while (number in check_wrap):
            random_list = random.sample(digits, 4)
            number = ''.join(random_list)
            number = str(2016 + i) + number
        check_wrap.append(number)

        random_list = random.sample(letters, 10)  # storing name
        name = ''.join(random_list).upper()

        random_list = random.sample(letters, 50)  # storing address
        address = ''.join(random_list).upper()

        s = Student(number, name, address)
        student_list.append(s)

    check_wrap.clear()

random.shuffle(student_list)  # shuffle year of student number

for i in range(20000):
    f.write("number : " + student_list[i].number + " ")
    f.write("name : " + student_list[i].name + " ")
    f.write("address : " + student_list[i].address + '\n')

print("storing end")
f.close()

f = open("student_information.txt", "r", encoding="utf8")
check_list = []
for i in range(20000):
    temp = f.readline()
    temp = temp[9:17]
    if (temp in check_list):
        print("ERROR!")
        exit()
    check_list.append(temp)
print("all the information is different")
f.close()
