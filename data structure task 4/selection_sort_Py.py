import time as t

f = open("student_information.txt", "r", encoding="utf8")


class Student():
    def __init__(self, number, name, address):
        self.number = number
        self.name = name
        self.address = address

# selection sort definition


def selection_sort(arr, check):
    if (check == "number"):
        n = len(arr)
        for i in range(n - 1):
            least = i
            for j in range(i + 1, n):
                if (arr[j].number < arr[least].number):
                    least = j
            arr[i], arr[least] = arr[least], arr[i]
    elif (check == "name"):
        n = len(arr)
        for i in range(n - 1):
            least = i
            for j in range(i + 1, n):
                if (arr[j].name < arr[least].name):
                    least = j
            arr[i], arr[least] = arr[least], arr[i]


student_list = []
information_list = f.readlines()  # one line element list

for i in range(len(information_list)):
    student = Student(
        information_list[i][9: 17], information_list[i][25: 35], information_list[i][46: 96])
    student_list.append(student)

print("<python, selection sort>")
# sorting by number
copy_list = student_list[:]  # for unchanging original array
start = t.time()
selection_sort(copy_list, "number")
end = t.time()
print("sort by number : " +
      str(int(round((end - start) * 1000)) / 1000) + "sec")

# check sort by number

is_sorted = all(copy_list[i].number < copy_list[i +
                                                1].number for i in range(len(copy_list) - 1))
print("sort by number is good? ", end="")
print(is_sorted)

# sorting by name
copy_list = student_list[:]
start = t.time()
selection_sort(copy_list, "name")
end = t.time()
print("sort by name : " +
      str(int(round((end - start) * 1000)) / 1000) + "sec")

# check sort by name

is_sorted = all(copy_list[i].name < copy_list[i +
                1].name for i in range(len(copy_list) - 1))
print("sort by name is good? ", end="")
print(is_sorted)
