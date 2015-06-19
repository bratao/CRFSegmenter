#ifndef HOCRF_HIGH_ORDER_CRF_DATA_SEQUENCE_H
#define HOCRF_HIGH_ORDER_CRF_DATA_SEQUENCE_H

#include "types.h"

#include "Feature.h"
#include "FeatureTemplate.h"
#include "LabelSequence.h"

#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace HighOrderCRF {

using std::shared_ptr;
using std::unordered_map;
using std::unordered_set;
using std::vector;

class PatternSetSequence;

class DataSequence
{
public:
    DataSequence(shared_ptr<vector<vector<shared_ptr<FeatureTemplate>>>> featureTemplateListList,
                 shared_ptr<vector<label_t>> labels,
                 shared_ptr<vector<unordered_set<label_t>>> possibleLabelTypeSetList,
                 bool hasValidLabels);
    size_t length() const;
    shared_ptr<LabelSequence> getLabelSequence(size_t pos, size_t length) const;
    void accumulateFeatureData(unordered_map<shared_ptr<FeatureTemplate>, vector<uint32_t>> *featureTemplateToFeatureIndexListMap, unordered_map<shared_ptr<Feature>, uint32_t> *featureToFeatureIndexMap, vector<double> *featureCountList) const;
    shared_ptr<PatternSetSequence> generatePatternSetSequence(const unordered_map<shared_ptr<FeatureTemplate>, vector<uint32_t>> &featureTemplateToFeatureIndexListMap, const vector<uint32_t> &featureLabelSequenceIndexList, const vector<LabelSequence> &labelSequenceList) const;
private:
    shared_ptr<vector<vector<shared_ptr<FeatureTemplate>>>> featureTemplateListList;
    shared_ptr<vector<label_t>> labels;
    bool hasValidLabels;
    shared_ptr<vector<unordered_set<label_t>>> possibleLabelTypeSetList;
private:
};

}  // namespace HighOrderCRF
#endif  // HOCRF_HIGH_ORDER_CRF_DATA_SEQUENCE_H
