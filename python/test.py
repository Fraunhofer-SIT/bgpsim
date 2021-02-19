#!/usr/bin/env python3

__CAIDA_TEST = """
# <provider-as>|<customer-as>|-1
# <peer-as>|<peer-as>|0
1|2|-1|bgp
1|3|-1|bgp
2|3|0|bgp
2|4|-1|bgp
2|5|-1|bgp
3|6|-1|bgp
7|2|-1|bgp
"""

if __name__ == '__main__':
    from pybgpsim import CaidaReader, Graph, GraphSearch

    g = Graph()
    r = CaidaReader(g)
    r.ReadString(__CAIDA_TEST)
    s = GraphSearch(g)

    for i in range(1, 8):
        for j in range(i, 8):
            path = s.GetPath(i, j)
            print("Path from %d to %d: %s" % (i, j, path))