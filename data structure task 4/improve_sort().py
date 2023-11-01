import time as t
f = open("student_information.txt", "r", encoding="utf8")


class Student():
    def __init__(self, number, name, address):
        self.number = number
        self.name = name
        self.address = address


student_list = []
information_list = f.readlines()  # one line element list
dic_by_num = {}
dic_by_name = {}
for i in range(len(information_list)):
    student = Student(
        int(information_list[i][9: 17]), information_list[i][25: 35], information_list[i][46: 96])
    student_list.append(student)
# print(student_list[0].number, student_list[0].name, student_list[0].address)

for i in range(len(information_list)):  # make key : number dictionary
    student = Student(
        int(information_list[i][9: 17]), information_list[i][25: 35], information_list[i][46: 96])
    dic_by_num[student.number] = [student.name, student.address]

for i in range(len(information_list)):  # make key : name dictionary
    student = Student(
        int(information_list[i][9: 17]), information_list[i][25: 35], information_list[i][46: 96])
    dic_by_name[student.name] = [student.number, student.address]

key_num = []
for key, value in dic_by_num.items():
    key_num.append(key)
start = t.time()
key_num.sort()
end = t.time()
print("sort by number : " + str(int(round((end - start) * 1000)) / 1000) + "sec")

key_name = []
for key, value in dic_by_name.items():
    key_name.append(key)
start = t.time()
key_name.sort()
end = t.time()
print("sort by name : " + str(int(round((end - start) * 1000)) / 1000) + "sec")

f.close()
