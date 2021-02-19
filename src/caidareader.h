#pragma once

namespace BGPSim {
class CaidaReader;
}

#include <inttypes.h>
#include <stdlib.h>

#include "graph.h"
#include "reader.h"

namespace BGPSim {
class CaidaReader : public Reader {
 public:
  explicit CaidaReader(Graph *g);

 private:
  Graph *g_;
  void ParseLine(char *line) override;
};
}  // namespace BGPSim
