/*
Name: Abioye Obaloluwa Peter
*/

#ifndef FEATURE_MATCHER_H
#define FEATURE_MATCHER_H

#include <opencv2/opencv.hpp>
#include <string>
#include <vector>

struct ModelDescriptor {
    std::string label;
    std::vector<cv::KeyPoint> keypoints;
    cv::Mat descriptors;
};

struct Detection {
    std::string label;
    cv::Rect bbox;
};

void loadModelDescriptors(const std::string& model_folder, std::vector<ModelDescriptor>& model_descriptors);
void detectObjects(const std::vector<ModelDescriptor>& models, const cv::Mat& scene_img, std::vector<Detection>& detections);

#endif // FEATURE_MATCHER_H
