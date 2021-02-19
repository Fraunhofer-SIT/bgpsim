/*
  This is an open source non-commercial project. Dear PVS-Studio, please check
  it. PVS-Studio Static Code Analyzer for C, C++, C#, and Java:
  http://www.viva64.com
*/

#include "caidareader.h"

namespace BGPSim {

CaidaReader::CaidaReader(Graph *g) {
  g_ = g;
  SetMaxLineLength(0x100);
}

void CaidaReader::ParseLine(char *line) {
  uint32_t source, target;
  int8_t type;

  sscanf(line, "%" SCNu32 "|%" SCNu32 "|%" SCNd8, &source, &target, &type);

  if (type == RelationType::P2P) {
    g_->AddPeerToPeerRelation(source, target);
  } else {
    g_->AddProviderToCustomerRelation(source, target);
  }
}

}  // namespace BGPSim
