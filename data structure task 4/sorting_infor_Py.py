import time as t

f = open("student_information.txt", "r", encoding="utf8")


class Student():
    def __init__(self, number, name, address):
        self.number = number
        self.name = name
        self.address = address


student_list = []
information_list = f.readlines()  # one line element list

for i in range(len(information_list)):
    student = Student(
        information_list[i][9: 17], information_list[i][25: 35], information_list[i][46: 96])
    student_list.append(student)
# print(student_list[0].number, student_list[0].name, student_list[0].address)

start = t.time()
student_list.sort(key=lambda x: x.number)  # sorting about number
# for i in student_list:
#    print(i.number, i.name, i.address)
end = t.time()
print("sort by number : " + str(int(round((end - start) * 1000)) / 1000) + "sec")

start = t.time()
student_list.sort(key=lambda x: x.name)  # sorting about name
# for i in student_list:
#    print(i.number, i.name, i.address)
end = t.time()
print("sort by name : " + str(int(round((end - start) * 1000)) / 1000) + "sec")

f.close()
