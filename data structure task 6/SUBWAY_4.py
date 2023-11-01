import heapq


class Node:
    def __init__(self, station):  # 역 번호, 인접 역 정보
        self.station = station
        self.adjacent = {}

    def add_adjacent_node(self, ad_station, distance):  # 인접 역 번호, 인접 역 까지의 거리
        self.adjacent[ad_station] = distance


class SubwayGraph:
    def __init__(self):
        self.nodes = {}

    def add_node(self, node):
        self.nodes[node.station] = node.adjacent


def dijkstra(graph, start, destination):
    distances = {node: float('inf')
                 for node in graph}  # start로 부터의 거리 값을 저장하기 위함
    distances[start] = 0  # 시작 값은 0이어야 함
    queue = []
    # 시작 노드부터 탐색 시작 하기 위함.
    heapq.heappush(queue, [distances[start], start, [start]])

    while queue:  # queue에 남아 있는 노드가 없으면 끝
        # 탐색 할 노드, 거리를 가져옴.
        current_distance, current_destination, path = heapq.heappop(queue)

        if current_destination == destination:  # 도착지점에 도달하면 종료
            break

        if distances[current_destination] < current_distance:  # 기존에 있는 거리보다 길다면, 볼 필요도 없음
            continue

        for new_destination, new_distance in graph[current_destination].items():
            distance = current_distance + new_distance  # 해당 노드를 거쳐 갈 때 거리
            if distance < distances[new_destination]:  # 알고 있는 거리 보다 작으면 갱신
                distances[new_destination] = distance
                new_path = path + [new_destination]  # 새로운 경로 생성
                heapq.heappush(queue, [distance, new_destination, new_path])

    return distances[destination], path


f = open("subway_20222663.txt", "r")
information = []
subway_name = []  # 지하철에 번호를 매김(배열 인덱스로) -> 번호로 노드 접근
while True:
    line = f.readline()
    if not line:
        break
    line = line.replace('-', ' ').replace('/',
                                          ' ').replace('\n', '')  # 정보 공백으로 나누기
    temp = line.split()
    information.append(temp)
f.close()

arr_station = []
for i in range(len(information)):
    subway_name.append(information[i][1])  # 역 이름 저장
    arr_station.append(Node(i))  # 역 노드 생성

    del information[i][0]  # 역 번호와 이름 지우기
    del information[i][0]

for i in range(len(information)):
    while information[i]:
        arr_station[i].add_adjacent_node(int(information[i][0]), float(
            information[i][1]))  # 인접 역 정보 node.adjacent에 저장
        del information[i][0]
        del information[i][0]


subway = SubwayGraph()  # 지하철 그래프 생성

for node in arr_station:  # 그래프 그리기
    subway.add_node(node)

for i in range(len(subway_name)):
    print(subway_name[i] + ": " + str(i))

start = int(input("\n출발 지점: "))
end = int(input("도착 지점: "))
distance, path = dijkstra(subway.nodes, start, end)
for i in range(len(path)):
    path[i] = subway_name[path[i]]


print("\n최단거리는 : " + str(distance))

print("경로는 다음과 같습니다.")
print(path[0], end="")
for i in range(1, len(path)):
    print(" >> " + path[i], end="")
print("")
