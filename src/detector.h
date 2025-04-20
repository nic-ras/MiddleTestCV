#ifndef DETECTOR_H
#define DETECTOR_H

#include <vector>

#include "dataset.h"
#include "detectiondefs.h"
#include "performance.h"

// TODO
// Use as base class for more specialized detectors if needed.
class Detector
{
public:
    virtual std::shared_ptr<DetectionTaskResult> detect(const Dataset &dataset);
};

#endif