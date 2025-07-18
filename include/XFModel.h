#ifndef XFMODEL_H
#define XFMODEL_H

#include <torch/torch.h>

namespace XFeat {
struct BasicLayerImpl : torch::nn::Module {
  /*
      Basic Convolutional Layer: Conv2d -> BatchNorm -> ReLU
  */
  torch::nn::Sequential layer;

  BasicLayerImpl(int in_channels,
                 int out_channels,
                 int kernel_size = 3,
                 int stride = 1,
                 int padding = 1,
                 int dilation = 1,
                 bool bias = false);
  torch::Tensor forward(torch::Tensor x);
};

TORCH_MODULE(BasicLayer);

struct XFeatModel : torch::nn::Module {
  /*
      C++ implementation (declaration) of architecture described in
      "XFeat: Accelerated Features for Lightweight Image Matching, CVPR 2024."
  */
  torch::nn::InstanceNorm2d norm{nullptr};
  torch::nn::Sequential skip1{nullptr};
  torch::nn::Sequential block1{nullptr}, block2{nullptr}, block3{nullptr},
      block4{nullptr}, block5{nullptr};
  torch::nn::Sequential block_fusion{nullptr}, heatmap_head{nullptr},
      keypoint_head{nullptr};
  torch::nn::Sequential fine_matcher{nullptr};

  XFeatModel(int stride = 4);  // Default stride of 4 to match Python version
  torch::Tensor unfold2d(torch::Tensor& x, int ws = 2);
  std::tuple<torch::Tensor, torch::Tensor, torch::Tensor> forward(
      torch::Tensor& x);
};
}  // namespace XFeat

#endif  // XFMODEL_H