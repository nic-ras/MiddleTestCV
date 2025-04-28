#ifndef UTILS_H
#define UTILS_H

#include <opencv2/opencv.hpp>
#include <vector>
#include <string>
#include "feature_matcher.h"

void drawDetections(cv::Mat& img, const std::vector<Detection>& detections);
void saveDetections(const std::string& filename, const std::vector<Detection>& detections);
cv::Mat preprocessImage(const cv::Mat& input);

#endif // UTILS_H
