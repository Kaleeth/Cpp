#include <memory>
#include <string>
#include <vector>

struct Pizza {
    float diameter;
    std::vector<std::string> toppings;
};

std::unique_ptr<Pizza>
make_unique_pepperoni_pizza(float diameter) {
    std::vector<std::string> toppings{"red sauce", "cheese", "pepperoni"};
    return std::make_unique<Pizza>(diameter, toppings);
}

void convert_unique_to_shared_is_easy_and_cheap() {
    auto pizza = make_unique_pepperoni_pizza(16.0f);
    std::shared_ptr<Pizza> shared_pizza = std::move(pizza);
    // or...
    // std::shared_ptr<Pizza> shared_pizza = make_unique_pepperoni_pizza(16.0f);
}