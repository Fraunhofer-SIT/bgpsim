/*
  This is an open source non-commercial project. Dear PVS-Studio, please check
  it. PVS-Studio Static Code Analyzer for C, C++, C#, and Java:
  http://www.viva64.com
*/

#include <stdio.h>
#include <string>
#include "bgpsim.h"

char const *relations =
    "# <provider-as>|<customer-as>|-1\n"
    "# <peer-as>|<peer-as>|0\n"
    "1|2|-1\n"
    "1|3|-1\n"
    "2|3|0\n"
    "2|4|-1\n"
    "2|5|-1\n"
    "3|6|-1\n"
    "7|2|-1";

int main() {
  BGPSim::Graph g;
  BGPSim::CaidaReader reader(&g);
  reader.ReadString(relations);
  BGPSim::GraphSearch s(&g);

  g.PrintStats();
  g.PrintNodes();

  for (int i = 1; i < 8; ++i) {
    for (int j = i; j < 8; ++j) {
      printf(">> Getting path from %d to %d:\n", i, j);
      auto path = s.GetPath(i, j);
      for (auto &node : path) {
        printf(" %d", node);
      }
      printf("\n");
    }
  }

  return 0;
}
