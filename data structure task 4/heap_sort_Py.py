import time as t

f = open("student_information.txt", "r", encoding="utf8")


class Student():
    def __init__(self, number, name, address):
        self.number = number
        self.name = name
        self.address = address

# heap sort definition


def heap_sort(arr, check):
    if (check == "number"):
        hsize = len(arr) - 1
        for i in reversed(range(1, hsize // 2 + 1)):
            adjust_number(arr, i, hsize)

        for i in range(hsize):
            arr[1], arr[hsize] = arr[hsize], arr[1]
            adjust_number(arr, 1, hsize - 1)
            hsize -= 1

    elif (check == "name"):
        hsize = len(arr) - 1
        for i in reversed(range(1, hsize // 2 + 1)):
            adjust_name(arr, i, hsize)

        for i in range(hsize):
            arr[1], arr[hsize] = arr[hsize], arr[1]
            adjust_name(arr, 1, hsize - 1)
            hsize -= 1


def adjust_number(arr, i, size):
    while (2 * i <= size):
        k = 2 * i
        if (k < size and arr[k].number < arr[k + 1].number):
            k += 1
        if (arr[i].number >= arr[k].number):
            break
        arr[i], arr[k] = arr[k], arr[i]
        i = k


def adjust_name(arr, i, size):
    while (2 * i <= size):
        k = 2 * i
        if (k < size and arr[k].name < arr[k + 1].name):
            k += 1
        if (arr[i].name >= arr[k].name):
            break
        arr[i], arr[k] = arr[k], arr[i]
        i = k


student_list = []
information_list = f.readlines()  # one line element list

for i in range(len(information_list)):
    student = Student(
        information_list[i][9: 17], information_list[i][25: 35], information_list[i][46: 96])
    student_list.append(student)

print("<python, heap sort>")
# sorting by number
copy_list = student_list[:]
copy_list.insert(0, 0)  # heap sort's starting index is 1
start = t.time()
heap_sort(copy_list, "number")
del copy_list[0]
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
copy_list.insert(0, 0)
start = t.time()
heap_sort(copy_list, "name")
del copy_list[0]
end = t.time()
print("sort by name : " +
      str(int(round((end - start) * 1000)) / 1000) + "sec")

# check sort by name

is_sorted = all(copy_list[i].name < copy_list[i +
                                              1].name for i in range(len(copy_list) - 1))
print("sort by name is good? : ", end="")
print(is_sorted)
