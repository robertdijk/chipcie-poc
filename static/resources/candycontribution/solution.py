from heapq import *

n, m = [int(x) for x in input().split()]
s, t, c = [int(x) for x in input().split()]

# The front of the pq should be the max. number of candies, so it's negative
graph = [dict() for _ in range(n + 1)]
pq = [(-c, s)]
done = set()

# Build the graph: for each edge, store tax percentage for both vertices
edges = [[int(x) for x in input().split()] for _ in range(m)]
for u, v, p in edges:
    graph[u][v] = p
    graph[v][u] = p

while pq:
    candy, curr = heappop(pq)
    if curr == t:
        print(-int(candy)), exit()
    if curr in done:
        continue
    done.add(curr)
    for neigh, tax in graph[curr].items():
        if neigh not in done:
            # Use floor-division instead of ceil-division, because candies are negative
            heappush(pq, (candy - candy * tax // 100, neigh))
