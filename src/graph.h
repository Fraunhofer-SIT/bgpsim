#pragma once

#include <inttypes.h>
#include <map>
#include <vector>

namespace BGPSim {
typedef uint32_t ASN;
typedef std::vector<ASN> ASNVec;
typedef std::vector<ASN> ASNPath;

enum RIR : uint8_t {
  UNASSIGNED = 0,
  APNIC,
  ARIN,
  RIPE,
  AFRINIC,
  LACNIC,
  last = LACNIC
};

struct AS {
  ASN number;
  RIR rir;
  ASNVec peers;
  ASNVec providers;
  ASNVec customers;
};
typedef std::vector<AS> ASVec;

enum RelationType : int8_t { P2C = -1, P2P = 0 };

class Graph {
 public:
  AS operator[](const int index);
  void AddProviderToCustomerRelation(ASN provider, ASN customer);
  void AddPeerToPeerRelation(ASN peer1, ASN peer2);
  void PrintStats();
  void PrintNodes();
  std::size_t GetNumNodes();
  ASN GetMaxASN();
  ASNVec GetAllASNs();
  ASNVec GetAllNodeWithCustomers(uint32_t min, uint32_t max);
  bool HasNode(ASN node);
  void ExcludeNodes(ASNVec exclude);
  bool IsExcluded(ASN node);

 protected:
  void CreateNode(ASN node);
  uint32_t num_edges_ = 0;
  uint32_t rirs_[6];
  ASN max_asn_ = 0;
  std::map<ASN, AS> nodes_;
  ASNVec asns_;
  ASNVec exclude_;
};
}  // namespace BGPSim
