import time as t

f = open("student_information.txt", "r", encoding="utf8")


class Student():
    def __init__(self, number, name, address):
        self.number = number
        self.name = name
        self.address = address

# quick sort definition


def quick_sort(arr, low, high):
    if (low < high):
        pivot = partition(arr, low, high)
        quick_sort(arr, low, pivot - 1)
        quick_sort(arr, pivot + 1, high)


def partition(arr, pivot, high):
    i = pivot + 1
    j = high
    while True:
        while (i < high and arr[i] < arr[pivot]):
            i += 1
        while (j > pivot and arr[j] > arr[pivot]):
            j -= 1
        if (j <= i):
            break
        arr[i], arr[j] = arr[j], arr[i]
        i += 1
        j -= 1
    arr[pivot], arr[j] = arr[j], arr[pivot]
    return j


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


print("<Python, improved quick sort>")
key_num = []
for key, value in dic_by_num.items():
    key_num.append(key)
start = t.time()
quick_sort(key_num, 0, len(key_num) - 1)
end = t.time()
print("sort by number : " + str(int(round((end - start) * 1000)) / 1000) + "sec")

key_name = []
for key, value in dic_by_name.items():
    key_name.append(key)
start = t.time()
quick_sort(key_name, 0, len(key_name) - 1)
end = t.time()
print("sort by name : " + str(int(round((end - start) * 1000)) / 1000) + "sec")
