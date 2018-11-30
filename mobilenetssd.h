#ifndef MOBILENETSSD_H
#define MOBILENETSSD_H

#include <caffe/caffe.hpp>
#include <caffe/net.hpp>
#include <fstream>
#include <iostream>
#include <opencv2/opencv.hpp>
#include <boost/shared_ptr.hpp>
using namespace caffe;
using namespace std;
using namespace cv;

typedef struct Obj_Info_
{
    Rect obj_box;
    float   obj_prob;
    int     obj_class;
}Obj_Info;

class MobileNetSSD
{
public:
    MobileNetSSD();
    //初始化模型
    void Initnet(string modelfile, string weights);
    //行人检测
    vector<Obj_Info> detect(cv::Mat &image);
    std::vector<cv::Rect> result;
    void destroydetect();

    boost::shared_ptr<Net<float> > net_;
    std::string model_file;
    std::string weights_file;
};



#endif // MOBILENETSSD_H
