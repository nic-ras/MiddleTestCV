#include "libraries.h"

int main(int argc, char** argv)
{
    // Load as grayscale
    const cv::Mat input = cv::imread("input.jpg", 0); 

    if (input.empty()) {
        std::cerr << "Impossible to load the image!" << std::endl;
        return -1;
    }

    // Create a SIFT detector
    cv::Ptr<cv::SIFT> siftPtr = cv::SIFT::create();

    // Detect the keypoints
    std::vector<cv::KeyPoint> keypoints;
    siftPtr->detect(input, keypoints);

    // Add results to image and save.
    cv::Mat output;
    cv::drawKeypoints(input, keypoints, output);
    cv::imwrite("sift_result.jpg", output);

    return 0;
}