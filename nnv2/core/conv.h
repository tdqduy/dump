#pragma once

#include "layer.h"
#include "initializer.h"

namespace nnv2 {

class Conv2D: public Layer {
public:
    Conv2D(int in_feats, int out_feats, int in_h, int in_w, int pad_h, int pad_w,
           int kernel_h, int kernel_w, int stride_h, int stride_w, const Initializer *init);

    void forward() override;
    void backward() override;

private:
    int in_feats;
    int out_feats;

    int in_h;
    int in_w;
    int pad_h;
    int pad_w;
    int kernel_h;
    int kernel_w;
    int stride_h;
    int stride_w;
    int out_h;
    int out_w;

    std::unique_ptr<Array> kernel;
    std::unique_ptr<Array> kernel_grad;

    std::unique_ptr<Array> bias;
    std::unique_ptr<Array> bias_grad;

    std::unique_ptr<Array> imcols;
};

void im2col(const Array *im, Array *imcols, int pad_h, int pad_w, int kernel_h, int kernel_w,
            int stride_h, int stride_w);

void col2im(const Array *imcols, Array *im, int pad_h, int pad_w, int kernel_h, int kernel_w,
            int stride_h, int stride_w);

void conv_forward(Array *output, const Array *input, Array *cols, Array *kernel,
                  int pad_h, int pad_w, int stride_h, int stride_w);

void conv_forward_bias(Array *output, const Array *bias);

void conv_backward(Array *input_grad, Array *kernel_grad, Array *output_grad, const Array *input,
                   Array *kernel, const Array *cols, int pad_h, int pad_w, int stride_h,
                   int stride_w);

void conv_backward_bias(Array *bias_grad, const Array *output_grad);

} // namespace nnv2