#include <algorithm>
#include <cassert>
#include <memory>
#include <sstream>
#include <string>
#include <vector>

#include "WordFeatureGenerator.h"

namespace DataConverter {

using std::make_shared;
using std::max;
using std::min;
using std::shared_ptr;
using std::showpos;
using std::string;
using std::stringstream;
using std::vector;

using HighOrderCRF::FeatureTemplate;

WordFeatureGenerator::WordFeatureGenerator(size_t maxNgram, size_t maxWindow, size_t maxLabelLength) {
    this->maxNgram = maxNgram;
    this->maxWindow = maxWindow;
    this->maxLabelLength = maxLabelLength;
}

vector<vector<FeatureTemplate>> WordFeatureGenerator::generateFeatureTemplates(const vector<string> &observationList) const {
    vector<vector<FeatureTemplate>> featureTemplateListList(observationList.size());
    for (size_t pos = 0; pos < observationList.size(); ++pos) {
        int startPos = max(0, (int)pos - (int)maxWindow);
        size_t endPos = min(observationList.size(), pos + maxWindow + 1);
        assert(startPos >= 0);

        for (size_t curPos = startPos; curPos <= pos + 1; ++curPos) {
            size_t maxN = min(endPos - curPos, maxNgram);
            int curPosOffset = curPos - pos;

            stringstream prefix;
            prefix << "W" << showpos << curPosOffset << "/";
            for (size_t n = 1; n <= maxN; ++n) {
                if (curPos + n < pos || curPos > pos + 1) {
                    continue;
                }
                string obs(prefix.str());
                for (size_t offset = 0; offset < n; ++offset) {
                    obs += observationList[curPos + offset];
                    if (offset < n - 1) {
                        obs += "_";
                    }
                }
                size_t maxLen = min(maxLabelLength, pos - curPos + 2);
                for (size_t labelLength = 1; labelLength <= maxLen; ++labelLength) {
                    featureTemplateListList[pos].emplace_back(obs, labelLength);
                }
            }
        }
    }
    return featureTemplateListList;
}

}  // namespace DataConverter
