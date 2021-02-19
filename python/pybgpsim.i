%module pybgpsim

%include "inttypes.i"
%include "std_string.i"
%include "std_vector.i"


// Add necessary symbols to generated header
%{
typedef uint32_t ASN;
typedef std::vector<ASN> ASNPath;
typedef std::vector<ASN> ASNVec;
#include "graph.h"
#include "graphsearch.h"
#include "reader.h"
#include "caidareader.h"
using namespace BGPSim;
%}

%ignore BGPSim::Graph::operator[];
typedef uint32_t ASN;
typedef std::vector<ASN> ASNPath;
typedef std::vector<ASN> ASNVec;
%template(ASNVec) std::vector<ASN>;

// Process symbols n header
%include "graph.h"
%include "graphsearch.h"
%include "reader.h"
%include "caidareader.h"