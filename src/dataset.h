#ifndef DATASET_H
#define DATASET_H

#include <unordered_map>
#include <vector>

#include <opencv2/opencv.hpp>

struct Model
{
    std::string objectId; // this is the id of the object, e.g. sugar box has id 004 (004_sugar_box)
    std::string modelId; // this is the id of the model, e.g. view_30_006_mask.png has id 006
    std::string degree;
    cv::Mat color;
    cv::Mat mask;
};

struct Label
{
    std::string objectId;
    std::string objectName;
    int xmin;
    int ymin;
    int xmax;
    int ymax;
};

// TODO
class Dataset
{
public:
    static Dataset load(std::string &folderPath);

    const std::unordered_map<std::string , cv::Mat> &getTestImages() const { return m_testImages; };
    const std::unordered_map<std::string, Model> &getModels() const { return m_models; };
    const std::unordered_map<std::string , Label> &getLabels() const { return m_labels; };

private:
    std::unordered_map<std::string , cv::Mat> m_testImages; // filename -> image
    std::unordered_map<std::string, Model> m_models; // filename -> model
    std::unordered_map<std::string , Label> m_labels; // filename -> label
};

#endif