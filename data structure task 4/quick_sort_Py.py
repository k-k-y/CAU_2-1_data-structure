import time as t

f = open("student_information.txt", "r", encoding="utf8")


class Student():
    def __init__(self, number, name, address):
        self.number = number
        self.name = name
        self.address = address

# quick sort definition


def quick_sort(arr, low, high, check):
    if (check == "number"):
        if (low < high):
            pivot = partition_number(arr, low, high)
            quick_sort(arr, low, pivot - 1, "number")
            quick_sort(arr, pivot + 1, high, "number")
    elif (check == "name"):
        if (low < high):
            pivot = partition_name(arr, low, high)
            quick_sort(arr, low, pivot - 1, "name")
            quick_sort(arr, pivot + 1, high, "name")


def partition_number(arr, pivot, high):
    i = pivot + 1
    j = high
    while True:
        while (i < high and arr[i].number < arr[pivot].number):
            i += 1
        while (j > pivot and arr[j].number > arr[pivot].number):
            j -= 1
        if (j <= i):
            break
        arr[i], arr[j] = arr[j], arr[i]
        i += 1
        j -= 1
    arr[pivot], arr[j] = arr[j], arr[pivot]
    return j


def partition_name(arr, pivot, high):
    i = pivot + 1
    j = high
    while True:
        while (i < high and arr[i].name < arr[pivot].name):
            i += 1
        while (j > pivot and arr[j].name > arr[pivot].name):
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

for i in range(len(information_list)):
    student = Student(
        information_list[i][9: 17], information_list[i][25: 35], information_list[i][46: 96])
    student_list.append(student)

print("<python, quick sort>")
# sorting by number
copy_list = student_list[:]
start = t.time()
quick_sort(copy_list, 0, len(copy_list) - 1, "number")
end = t.time()
print("sort by number : " +
      str(int(round((end - start) * 1000)) / 1000) + "sec")

# check sort by number

is_sorted = all(copy_list[i].number < copy_list[i +
                                                1].number for i in range(len(copy_list) - 1))
print("sort by number is good? : ", end="")
print(is_sorted)

# sorting by name
copy_list = student_list[:]
start = t.time()
quick_sort(copy_list, 0, len(copy_list) - 1, "name")
end = t.time()
print("sort by name : " +
      str(int(round((end - start) * 1000)) / 1000) + "sec")

# check sort by name

is_sorted = all(copy_list[i].name < copy_list[i +
                                              1].name for i in range(len(copy_list) - 1))
print("sort by name is good? : ", end="")
print(is_sorted)
