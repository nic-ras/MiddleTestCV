#include "libraries.h"

int SIFT( cv::Mat& original, cv::Mat& output,){

    cv::SiftFeatureDetector detector;
    std::vector<cv::KeyPoint> keypoints;
    detector.detect(original, keypoints);

    cv::drawKeypoints(input, keypoints, output);

    return 0;  

}