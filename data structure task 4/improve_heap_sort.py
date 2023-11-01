import time as t

f = open("student_information.txt", "r", encoding="utf8")


class Student():
    def __init__(self, number, name, address):
        self.number = number
        self.name = name
        self.address = address

# heap sort definition


def heap_sort(arr):
    hsize = len(arr) - 1
    for i in reversed(range(1, hsize // 2 + 1)):
        adjust(arr, i, hsize)
    for i in range(hsize):
        arr[1], arr[hsize] = arr[hsize], arr[1]
        adjust(arr, 1, hsize - 1)
        hsize -= 1


def adjust(arr, i, size):
    while (2 * i <= size):
        k = 2 * i
        if (k < size and arr[k] < arr[k + 1]):
            k += 1
        if (arr[i] >= arr[k]):
            break
        arr[i], arr[k] = arr[k], arr[i]
        i = k


student_list = []
information_list = f.readlines()  # one line element list
dic_by_num = {}
dic_by_name = {}

for i in range(len(information_list)):
    student = Student(
        int(information_list[i][9: 17]), information_list[i][25: 35], information_list[i][46: 96])
    student_list.append(student)

for i in range(len(information_list)):  # make key : number dictionary
    student = Student(
        int(information_list[i][9: 17]), information_list[i][25: 35], information_list[i][46: 96])
    dic_by_num[student.number] = [student.name, student.address]

for i in range(len(information_list)):  # make key : name dictionary
    student = Student(
        int(information_list[i][9: 17]), information_list[i][25: 35], information_list[i][46: 96])
    dic_by_name[student.name] = [student.number, student.address]


print("<Python, improved heap sort>")
key_num = []
key_num.append(0)
for key, value in dic_by_num.items():
    key_num.append(key)
start = t.time()
heap_sort(key_num)
del key_num[0]
end = t.time()
print("sort by number : " + str(int(round((end - start) * 1000)) / 1000) + "sec")

key_name = []
key_name.append(0)
for key, value in dic_by_name.items():
    key_name.append(key)
start = t.time()
heap_sort(key_name)
del key_name[0]
end = t.time()
print("sort by name : " + str(int(round((end - start) * 1000)) / 1000) + "sec")
