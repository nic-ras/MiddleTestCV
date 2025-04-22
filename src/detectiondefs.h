#ifndef DETECTIONDEFS_H
#define DETECTIONDEFS_H

#include <unordered_map>

#include "dataset.h"

// TODO
struct PerformanceResult
{
};

struct DetectionResult
{
    // use Label::toString to convert Labels to result string format if needed
    // result string: (<object_id>_<object_name> <xmin> <ymin> <xmax> <ymax>)
    std::unordered_map<std::string, std::vector<Label>> result; // filename -> labels of found objects
};

struct DetectionTaskResult
{
    DetectionResult detectionResult;
    PerformanceResult performanceResult;
};

#endif