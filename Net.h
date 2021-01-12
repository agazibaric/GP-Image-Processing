/*#pragma once
#include <torch/torch.h>

struct Net : torch::nn::Module {
    Net() {
        // Initialize CNN
        conv1 = register_module("conv1", torch::nn::Conv2d(torch::nn::Conv2dOptions(1, 10, 5)));
        conv2 = register_module("conv2", torch::nn::Conv2d(torch::nn::Conv2dOptions(10, 20, 5)));
        conv2_drop = register_module("conv2_drop", torch::nn::Dropout2d());
        fc1 = register_module("fc1", torch::nn::Linear(320, 50));
        fc2 = register_module("fc2", torch::nn::Linear(50, 10));
    }

    // Implement Algorithm
    torch::Tensor forward(torch::Tensor x) {
        x = torch::relu(torch::max_pool2d(conv1->forward(x), 2));
        x = torch::relu(torch::max_pool2d(conv2_drop->forward(conv2->forward(x)), 2));
        x = x.view({ -1, 320 });
        // x = x::view(-1, 320);
        // x = x.reshape({-1, 320});
        x = torch::relu(fc1->forward(x));
        x = torch::dropout(x, 0.5, is_training());
        x = fc2->forward(x);
        return torch::log_softmax(x, 1);
    }

    torch::nn::Conv2d conv1{ nullptr };
    torch::nn::Conv2d conv2{ nullptr };
    torch::nn::Dropout2d conv2_drop{ nullptr };
    torch::nn::Linear fc1{ nullptr }, fc2{ nullptr };
};*/