#include <vector>

void train_model(const std::vector<int> &data, auto &model) {
    for (const auto &x: data)
        model.update(x);
}