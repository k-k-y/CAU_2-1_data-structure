import math

global count
count = 0


def pre_visual(tree, index):
    global count
    if index < len(tree) and tree[index] is not None:
        if (index == 1):
            print(tree[index])

        elif (index % 2 == 0):  # left node
            if tree[index + 1]:
                count += 1
            for _ in range(count - 1):
                print("|  ", end="")
            for _ in range(math.floor(math.log2(index)) - count):
                print("   ", end="")

            print("|--", end="")
            print(tree[index])

        elif (index % 2 == 1):  # right node
            for _ in range(count - 1):
                print("|  ", end="")
            for _ in range(math.floor(math.log2(index)) - count):
                print("   ", end="")

            print("|--", end="")
            print(tree[index])
            count -= 1

        pre_visual(tree, 2 * index)
        pre_visual(tree, 2 * index + 1)


tree1 = [None, 1, 5, 3, 4, 2, 6, 7]
tree2 = [None, 1, 2, 3, 4, 5, 6, 7,
         8, 9, 10, 11, None, None, 14, 15]

pre_visual(tree1, 1)
