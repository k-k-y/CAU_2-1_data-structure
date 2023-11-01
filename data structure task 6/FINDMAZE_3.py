from collections import deque


def BFS(maze, col, row):
    start = [1, 1]
    end = [row - 2, col - 2]
    directions = [(1, 0), (0, -1), (-1, 0), (0, 1)]  # 동 서 남 북

    visited = [[0] * col for _ in range(row)]  # 방문 여부 배열
    prev = [[None] * col for _ in range(row)]  # 이전 노드 저장 배열

    queue = deque()
    queue.append([1, 1])
    visited[1][1] = 1

    while queue:
        i, j = queue.popleft()

        if [i, j] == end:
            break
        for di, dj in directions:  # 동서남북으로 차례대로 이동
            ni, nj = i + di, j + dj
            # 만약에 길이라면
            if (0 <= ni < row and 0 <= nj < col and visited[ni][nj] == 0 and maze[ni][nj] == ' '):
                queue.append([ni, nj])
                visited[ni][nj] = 1
                prev[ni][nj] = [i, j]

    shortest_path = maze[:]  # 최단 경로를 표시하기 위해 미로 복사

    cur = end
    len_path = 0
    while cur is not None:  # 최단 경로 표시
        len_path += 1
        shortest_path[cur[0]][cur[1]] = '#'
        cur = prev[cur[0]][cur[1]]

    return shortest_path, len_path


f = open("maze1 - graph.txt", "r")

col, row = map(str, f.readline().split())
col = int(col) * 2 + 1
row = int(row) * 2 + 1

maze = []
while True:
    line = f.readline()
    line = line.replace("\n", "")
    if not line:
        break
    line = line.replace("+", "O").replace("-", "O").replace("|", "O")
    temp = list(line)
    maze.append(temp)
f.close()

path, length = BFS(maze, col, row)

for i in range(row):
    for j in range(col):
        print(path[i][j], end="")
    print("")
print("최단 경로의 길이는 " + str(length) + " 입니다.")
