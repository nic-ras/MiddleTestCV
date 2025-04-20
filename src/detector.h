#ifndef DETECTOR_H
#define DETECTOR_H

#include <vector>

#include "dataset.h"
#include "performance.h"

struct DetectionResult
{
    // result string: (<object_id>_<object_name> <xmin> <ymin> <xmax> <ymax>)
    std::unordered_map<std::string, Label> result; // filename -> result strings

    // TODO
    // converts a label object to string in result string form
    static std::string label2String(const Label &label);
};

struct DetectionTaskResult
{
    DetectionResult detectionResult;
    PerformanceResult performanceResult;
};

// TODO
// Use as base class for more specialized detectors if needed.
class Detector
{
public:
    virtual std::shared_ptr<DetectionTaskResult> detect(const Dataset &dataset);
};

#endif