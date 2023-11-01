from collections import deque
from anytree import Node, RenderTree
stack = deque()
digit = []


def Priority(x):
    if (x == '+' or x == '-'):
        return 1
    if (x == '*' or x == '/'):
        return 2
    if (x == '('):
        return 0


def InfixtoPostfix(Infix):
    Postfix = []
    stack = deque()
    for i in Infix:
        if (type(i) is float):
            Postfix.append(i)
        elif (i == '('):
            stack.append(i)
        elif (i == ')'):
            top = stack.pop()
            while (top != '('):
                Postfix.append(top)
                top = stack.pop()
        else:
            while (stack and Priority(i) <= Priority(stack[-1])):
                Postfix.append(stack.pop())
            stack.append(i)
    while stack:
        Postfix.append(stack.pop())
    return Postfix


def PostfixtoTree(Postfix):
    stack = deque()
    for i in Postfix:
        if (str(i) not in "+-*/()"):
            node = Node(i)
            stack.append(node)
        else:
            right = stack.pop()
            left = stack.pop()
            node = Node(i, children=[left, right])
            stack.append(node)
    return stack.pop()


def preorder_traversal(node):
    if node:
        if type(node.name) is float:
            print("{:g}".format(node.name), end=" ")
        else:
            print(node.name, end=" ")
        for child in node.children:
            preorder_traversal(child)


def postorder_traversal(node):
    if node:
        for child in node.children:
            postorder_traversal(child)
        if type(node.name) is float:
            print("{:g}".format(node.name), end=" ")
        else:
            print(node.name, end=" ")


def evaluation(node):
    if node.is_leaf:
        return float(node.name)
    left = evaluation(node.children[0])
    right = evaluation(node.children[1])

    if node.name == '+':
        return left + right
    elif node.name == '-':
        return left - right
    elif node.name == '*':
        return left * right
    elif node.name == '/':
        return left / right


# input infix expression
expression = input()
count = 0
for x in expression:

    if (x not in '+-*/()'):
        digit.append(x)
        if (x.isdigit()):
            count += 1
    if (x in '+-*/()'):
        if (count != 0):
            stack.append(float(''.join(digit)))
            count = 0
        digit.clear()
        stack.append(x)
if (digit):
    stack.append(float(''.join(digit)))


postfix = InfixtoPostfix(stack)
expression_tree = PostfixtoTree(postfix)

for pre, fill, node in RenderTree(expression_tree):
    print("%s%s" % (pre, node.name))

print("prefix : ", end="")
preorder_traversal(expression_tree)
print("")

print("postfix : ", end="")
postorder_traversal(expression_tree)
print("")

result = evaluation(expression_tree)
print("result : " + "{:g}".format(result))
