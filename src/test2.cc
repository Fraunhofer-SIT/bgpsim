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

int main(int argc, char *argv[]) {
  BGPSim::Graph g;
  BGPSim::CaidaReader reader(&g);

  if (argc < 3 || argc > 4) {
    fprintf(stderr, "Usage: %s <from> <to>", argv[0]);
    fprintf(stderr, "Usage: %s <relations> <from> <to>", argv[0]);
    return -1;
  }

  BGPSim::ASN from;
  BGPSim::ASN to;
  if (argc == 3) {
    reader.ReadString(relations);
    from = atoi(argv[1]);
    to = atoi(argv[2]);
  } else {
    reader.ReadFile(argv[1]);
    from = atoi(argv[2]);
    to = atoi(argv[3]);
  }

  BGPSim::GraphSearch s(&g);

  printf(">> Getting path from %d to %d:\n", from, to);
  printf("    >> One-Directional :");
  auto path = s.GetPath(from, to);
  for (auto &node : path) {
    printf(" %d", node);
  }
  printf("\n");

  return 0;
}
