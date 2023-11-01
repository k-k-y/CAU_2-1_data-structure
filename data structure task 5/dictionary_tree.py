from collections import deque


class Node:
    def __init__(self, data):
        self.data = data
        self.left = None
        self.right = None


class BSTree:
    def __init__(self):
        self.root = None

    def insert(self, data):
        if self.root is None:
            self.root = Node(data)
            return
        node = self.root
        while node is not None:
            parent = node
            if node.data[0] > data[0]:
                node = node.left
            else:
                node = node.right
        if parent.data[0] > data[0]:
            parent.left = Node(data)
        else:
            parent.right = Node(data)

    def getHeight(self, root):
        if root is None:
            return -1

        leftHeight = self.getHeight(root.left) + 1
        rightHeight = self.getHeight(root.right) + 1

        return max(leftHeight, rightHeight)

    def count_by_levelorder(self):
        count = 0

        q = deque()
        q.append(self.root)

        while q:
            for _ in range(len(q)):
                node = q.popleft()
                if node is not None:
                    count += 1
                if node:
                    q.append(node.left)
                    q.append(node.right)

        return count

    def search_and_getLevel(self, word):
        level = 0
        q = deque()
        q.append(self.root)

        while q:
            for _ in range(len(q)):
                node = q.popleft()
                if (node is not None and node.data[0] == word):
                    return node.data[1], level + 1
                if node:
                    q.append(node.left)
                    q.append(node.right)
            level += 1


f = open("randdict_utf8.TXT", "r")

dict = BSTree()
count = 0
while True:
    line = f.readline()
    if not line:
        break
    token = line.index(" ")
    word = line[: token]
    meaning = line[token + 3: len(line) - 1]
    dict.insert([word, meaning])
    count += 1
f.close()

print("사전 파일을 모두 읽었습니다. " +
      str(count) + "개의 단어가 있습니다.")

count_by_level = dict.count_by_levelorder()  # eval words and height
height = dict.getHeight(dict.root) + 1
print("트리의 전체 높이는 " + str(height) + " 입니다. 트리의 노드 수는 " +
      str(count_by_level) + "개 입니다.")

while True:
    word = input("단어를 입력하세요 ")
    if (word == ""):  # exit condition
        break
    meaning, level = dict.search_and_getLevel(word)
    print(meaning + "(단어의 레벨 : " + str(level) + ")")
