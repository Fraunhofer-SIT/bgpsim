# libbgpsim / pybgpsim

A library for BGP simulations.

## Compile & Install

```
mkdir build
cd build
cmake ..
make
sudo make install
```

---
**NOTE**

Install may install the libraries into a folder where Python cannot find it. Copy the libraries to /usr/lib.
```
cp /usr/local/lib/libbgpsim.so /usr/lib/.
```
(as root or using sudo)


`CaidaReader` supports reading from _strings_ (with `ReadString`) and _files_
(`ReadFile`).


This simulator was highly optimized for our needs. In this state it will crash on invalid input data e.g. to large ASNs. Feel free to fork this project and adapt it to your needs.

---

## Usage (Python)

The `Graph` object is the main object. Everything else wraps around and need
a `Graph` object as a parameter:

```
from pybgpsim import CaidaReader, Graph, GraphSearch

g = Graph()
r = CaidaReader(g)
r.ReadString(__CAIDA_TEST)
s = GraphSearch(g)
```

There is also a `test.cc` in `src/` and a test.py in `python/`.
