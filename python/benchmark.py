#!/usr/bin/env python3

from pybgpsim import CaidaReader, Graph, GraphSearch, LegacyGraphSearch
import sys
import timeit

timeit.template = """
def inner(_it, _timer{init}):
    {setup}
    _t0 = _timer()
    for _i in _it:
        retval = {stmt}
    _t1 = _timer()
    return _t1 - _t0, retval
"""

if __name__ == '__main__':
    size = 20
    try:
        filename = sys.argv[1]
        if len(sys.argv) > 2:
            size = int(sys.argv[2])
    except Exception:
        sys.exit("usage: %s <relations file> [# of test ASNs (default: 20)]" %
                 sys.argv[0])

    def old():
        return [s1.GetPath(i, j) for i in x for j in x]

    def new():
        return [s2.GetPath(i, j) for i in x for j in x]

    print('Setting up...')
    g = Graph()
    r = CaidaReader(g)
    r.ReadFile(filename)

    s1 = LegacyGraphSearch(g)
    s2 = GraphSearch(g)

    x = g.GetAllASNs()[:size]

    t1 = timeit.Timer('old()', 'from __main__ import old')
    t2 = timeit.Timer('new()', 'from __main__ import new')

    sys.stdout.write('Calculating paths (old algorithm)...')
    sys.stdout.flush()
    r1 = t1.timeit(1)
    sys.stdout.write('\b\b\b: took %.4f seconds.\n' % r1[0])

    sys.stdout.write('Calculating paths (new algorithm)...')
    sys.stdout.flush()
    r2 = t2.timeit(3)
    sys.stdout.write('\b\b\b: took %.4f seconds.\n' % (r2[0] / 3.0))
    sys.stdout.flush()

    l1 = r1[1]
    l2 = r2[1]

    # this should never print since the paths should be the same!
    for i in range(size*size):
        if len(l1[i]) != len(l2[i]):
            print(l1[i])
            print(l2[i])
            print('---')
