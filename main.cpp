#include<iostream>
#include<mobilenetssd.h>
#include<opencv2/opencv.hpp>

using namespace cv;

int main()
{
    string modelfile = "/home/fuxueping/sdb/svn2018/model_acceleration/tensorRT/weight/mobileNetSSD/MobileNetSSD_deploy_ori.prototxt";
    string weights = "/home/fuxueping/sdb/svn2018/model_acceleration/tensorRT/weight/mobileNetSSD/MobileNetSSD_deploy.caffemodel";
    string imgDir = "/home/fuxueping/sdb/svn2018/model_acceleration/tensorRT/test_img/color_00050.jpg";



//    Blob<float> *input_data_blobs = net->input_blobs()[0];

    Mat img =imread(imgDir);
    MobileNetSSD mobileNetSSD;
    mobileNetSSD.Initnet(modelfile,weights);
    mobileNetSSD.detect(img);
//    mobileNetSSD.destroydetect();
    return 0;
}
