import heapq
def dijkstra(graph, start):
    d={node :float('inf') for node in graph}
    d[start]=0
    pq=[(0,start)]
    while pq:
        curr_dist,node=heapq.heappop(pq)
        if curr_dist>d[node]:
            continue
        for ne,we in graph[node]:
            nd=curr_dist+we
            if nd<d[ne]:
                d[ne]=nd
                heapq.heappush(pq,(nd,ne))
    return d
n=int(input("Enter no of vertices:"))
e=int(input("Enter no of edges:"))
g={i: [] for i in range(n)}
print("Enter Edges (source Destination Weight):")
for _ in range(e):
    u,v,w=map(int,input().split())
    g[u].append((v,w))
    g[v].append((u,w))
start=int(input("Enter starting node:"))
result=dijkstra(g,start)
print("Shortest distances from source",start, " :")
for node in range(n):
    print(f"{start}->{node}: {result[node]}")