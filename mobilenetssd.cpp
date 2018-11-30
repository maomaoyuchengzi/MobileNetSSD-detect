#include "mobilenetssd.h"
#include <QDebug>

MobileNetSSD::MobileNetSSD()
{

}


void MobileNetSSD::Initnet(string modelfile, string weights)
{
    this->model_file = modelfile;
    this->weights_file = weights;
}



vector<Obj_Info> MobileNetSSD::detect(cv::Mat &image)
{
//    vector<Rect> boxes;
    vector<Obj_Info> boxes;

     Mat img = image.clone();
    img.convertTo(img, CV_32FC3);   //转为浮点图
    Caffe::set_mode(Caffe::GPU);
    net_.reset(new Net<float>(model_file, TEST));
    net_->CopyTrainedLayersFrom(weights_file);

    Blob<float>* inputBlob = net_->input_blobs()[0];
    int width = inputBlob->width();            //网络规定的输入图片的宽度和高度
    int height = inputBlob->height();
    cv::resize(img, img, cv::Size(width, height));     //将测试图片进行调整大小 48 * 48
    inputBlob->Reshape(1, 3, height, width);
    net_->Reshape();

    img = (img - 127.5)*0.007843;
    float* data = inputBlob->mutable_cpu_data();   //将图片的像素值，复制进网络的输入Blob
    for (int k = 0; k<3; ++k){
        for (int i = 0; i<height; ++i){
            for (int j = 0; j<width; ++j){
                int index = (k*height + i)*width + j;  //获取偏移量
                data[index] = img.at<cv::Vec3f>(i, j)[k];
            }
        }
    }
    FILE *fp = fopen("/home/fuxueping/sdb/svn2018/model_acceleration/tensorRT/result/output/data_demo.txt","w");
    int data_count = 3*300*300;
    for(int i = 0; i < data_count;i++)
    {
    //            fprintf(fp,"%f\n",malloc_image_ptr[i]);
       fprintf(fp,"%f\n",data[i] );
    }
    fclose(fp);

    net_->ForwardFrom(0);
    Blob<float>* result_blob = net_->output_blobs()[0];
    const float* result = result_blob->cpu_data();
    const int num_det = result_blob->height();

    for (int k = 0; k < num_det; ++k)
    {
        Obj_Info obj;
        if (result[0] == -1) {
          // Skip invalid detection.
          result += 7;
          continue;
        }
        if( (result[1] == 15) && (result[2] > 0.5) )
        {
            obj.obj_class = result[1];
            obj.obj_prob = result[2];
            int minx = int(result[3] * image.cols);
            int miny = int(result[4] * image.rows);
            int maxx = int(result[5] * image.cols);
            int maxy = int(result[6] * image.rows);

            minx = max(0, minx);
            miny = max(0, miny);
            maxx = min(image.cols - 1, maxx);
            maxy = min(image.rows - 1, maxy);

            Rect box;
            box.x = minx;
            box.y = miny;
            box.width = maxx - minx + 1;
            box.height = maxy - miny + 1;
            obj.obj_box = box;
            boxes.push_back(obj);
        }
        result += 7;
    }
    return boxes;
}



