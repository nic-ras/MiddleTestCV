/*
Name: Abioye Obaloluwa Peter
*/

#include "utils.h"
#include <fstream>

void drawDetections(cv::Mat& img, const std::vector<Detection>& detections) {
    for (const auto& d : detections) {
        cv::rectangle(img, d.bbox, cv::Scalar(0, 255, 0), 2);
        cv::putText(img, d.label, d.bbox.tl(), cv::FONT_HERSHEY_SIMPLEX, 0.5, cv::Scalar(255, 0, 0), 1);
    }
}

void saveDetections(const std::string& filename, const std::vector<Detection>& detections) {
    std::ofstream ofs(filename);
    for (size_t i = 0; i < detections.size(); ++i) {
        ofs << i << "_" << detections[i].label << " "
            << detections[i].bbox.x << " " << detections[i].bbox.y << " "
            << detections[i].bbox.x + detections[i].bbox.width << " "
            << detections[i].bbox.y + detections[i].bbox.height << std::endl;
    }
}

cv::Mat preprocessImage(const cv::Mat& input) {
    cv::Mat gray, blurred, bilateral, edges, mask, output;

    // 1. Convert input to grayscale
    cv::cvtColor(input, gray, cv::COLOR_BGR2GRAY);

    // 2. Apply Gaussian Blur
    cv::GaussianBlur(gray, blurred, cv::Size(5, 5), 1.5);

    // 3. Apply Bilateral Filter
    cv::bilateralFilter(blurred, bilateral, 9, 75, 75);

    // 4. Edge Detection with Canny
    cv::Canny(bilateral, edges, 50, 150);

    // 5. Morphological Closing to remove small gaps
    cv::Mat kernel = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(3, 3));
    cv::morphologyEx(edges, edges, cv::MORPH_CLOSE, kernel);

    // 6. Create a mask from edges
    cv::bitwise_not(edges, mask);

    // 7. Apply the mask to the original color image
    input.copyTo(output, mask);

    return output;
}
