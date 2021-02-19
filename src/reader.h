#pragma once

namespace BGPSim {
class Reader;
}

#include <string>

namespace BGPSim {
class Reader {
 public:
  Reader() {}
  virtual ~Reader() {}
  void ReadString(std::string filename);
  void ReadString(const char *filename);
  void ReadFile(std::string filename);
  void ReadFile(const char *filename);
  virtual void ParseLine(char *line) = 0;
  void SkipComments(bool enabled);
  void SetMaxLineLength(size_t length);

 private:
  bool skipcomments_ = true;
  char commentchar_ = '#';
  size_t maxlinelength_ = 0x100000;
};

}  // namespace BGPSim
