#ifndef HOCRF_MAX_ENT_OBSERVATION_H_
#define HOCRF_MAX_ENT_OBSERVATION_H_

#include <memory>
#include <ostream>
#include <set>
#include <string>
#include <unordered_map>
#include <unordered_set>

namespace MaxEnt {

using std::ostream;
using std::set;
using std::shared_ptr;
using std::string;
using std::unordered_map;
using std::unordered_set;
class CompiledData;

class Observation
{
public:
    Observation(unordered_set<string> attributeSet, string correctLabel, set<string> possibleLabelSet);
    shared_ptr<CompiledData> compile(shared_ptr<unordered_map<string, size_t>> strToIndexMap, bool extendMap) const;
    void output(ostream &os);
    
private:
    unordered_set<string> attributeSet;
    string correctLabel;
    set<string> possibleLabelSet;
};

}  // namespace MaxEnt
#endif  // HOCRF_MAX_ENT_OBSERVATION_H_
