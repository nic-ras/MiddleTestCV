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

#endif