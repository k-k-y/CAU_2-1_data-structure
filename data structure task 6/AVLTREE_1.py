class AVLNode:
    def __init__(self, data):
        self.data = data
        self.left = None
        self.right = None
        self.height = 1


class AVLTree:
    def __init__(self):
        self.root = None

    def getHeight(self, node):  # 노드의 높이 반환 함수. 이게 있어야 None인 노드에 대해 예외처리(0 반환) 가능
        if node is None:
            return 0
        return node.height

    def getDif(self, node):  # 노드의 왼쪽 오른쪽 높이 차 반환
        if node is None:
            return 0
        return self.getHeight(node.left) - self.getHeight(node.right)

    def updateHeight(self, node):  # 높이 새로 업데이트
        if node is None:
            return
        node.height = max(self.getHeight(node.left),
                          self.getHeight(node.right)) + 1

    def insert(self, data):  # 트리에 노드 삽입
        self.root = self._insert(self.root, data)

    def _insert(self, node, data):
        if node is None:
            return AVLNode(data)
        if data[0] < node.data[0]:
            node.left = self._insert(node.left, data)
        else:
            node.right = self._insert(node.right, data)
        self.updateHeight(node)  # 노드 삽입할 때 마다 높이 업데이트 + 트리의 균형 잡기
        return self.balance(node)

    def balance(self, node):  # 트리 균형 잡기
        dif = self.getDif(node)
        if dif > 1:
            if self.getDif(node.left) < 0:  # LR rotate / else LL rotate
                node.left = self.left_rotate(node.left)
            return self.right_rotate(node)
        if dif < -1:
            if self.getDif(node.right) > 0:  # RL rotate / else RR rotate
                node.right = self.right_rotate(node.right)
            return self.left_rotate(node)
        return node

    def left_rotate(self, node):  # 왼쪽 회전(RR rotate)
        new_node = node.right
        node.right = new_node.left
        new_node.left = node

        self.updateHeight(node)
        self.updateHeight(new_node)
        return new_node

    def right_rotate(self, node):  # 오른쪽 회전(LL rotate)
        new_node = node.left
        node.left = new_node.right
        new_node.right = node

        self.updateHeight(node)
        self.updateHeight(new_node)
        return new_node

    def getTreeHeight(self, root):
        if root is None:
            return -1
        leftHeight = self.getTreeHeight(root.left) + 1
        rightHeight = self.getTreeHeight(root.right) + 1

        return max(leftHeight, rightHeight)

    def print_word(self):  # 중위 순회를 하면서 모든 단어, 뜻, 높이를 순차적으로 출력
        self.inorder_traversal(self.root)

    def inorder_traversal(self, node):
        if node:
            self.inorder_traversal(node.left)
            print(node.data[0], node.data[1], node.height)
            self.inorder_traversal(node.right)

    def search(self, word):  # 단어를 입력받으면 뜻을 반환하는 함수
        return self._search(self.root, word)

    def _search(self, node, word):
        if node is None or node.data[0] == word:
            return node.data[1]
        if word < node.data[0]:
            return self._search(node.left, word)
        else:
            return self._search(node.right, word)


f = open("randdict_utf8.TXT", "r")

dict = AVLTree()
while True:
    line = f.readline()
    if not line:
        break
    token = line.index(" ")
    word = line[: token]
    meaning = line[token + 3: len(line) - 1]
    dict.insert([word, meaning])
f.close()

dict_height = dict.getTreeHeight(dict.root) + 1
print("사전의 높이는 " + str(dict_height) + " 입니다.")

while True:
    word = input("단어를 입력하세요: ")
    if (word == ""):
        break
    print("뜻 : " + dict.search(word))
print("Finish :)")
