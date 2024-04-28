#ifndef __YOLO_HPP__
#define __YOLO_HPP__

namespace yolo{

struct Box {
  float left, top, right, bottom, confidence;
  int class_label;

  Box() = default;        // 启用默认构造函数
  // 有参构造函数，初始化列表初始化
  Box(float left, float top, float right, float bottom, float confidence, int class_label)
      : left(left),
        top(top),
        right(right),
        bottom(bottom),
        confidence(confidence),
        class_label(class_label) {}
};

struct Image{
  const void *bgrptr=nullptr;
  int width=0,height=0;

  Image()=default;
  Image(const void *bgrptr,int width,int height):bgrptr(bgrptr),width(width),height(height){};
};

typedef std::vector<Box> BoxArray;

class Infer{
 public:
  virtual BoxArray forward(const Image &image, void *stream = nullptr)=0;
  virtual std::vector<BoxArray> forwards(const std::vector<Image> &images,void *stream=nullptr)=0;
};

std::shared_ptr<Infer> load(const std::string &engine_file,
                            float confidence_threshold=0.25f,
                            float nms_threshold=0.5f);
} // namespace yolo

#endif    // __YOLO_HPP__