#include <iostream>
#include <string>
#include <vector>
#include <cmath>

// Глобальные переменные конфигурации
int MAX_DISCOUNT_PERCENT = 30;
double TAX_RATE = 0.20;
int MIN_ORDER_AMOUNT = 500;
std::string STORE_NAME = "Gallery of Scents";

struct Product {
    std::string name;
    double price;
    int stock;
};

struct Order {
    int id;
    std::string client;
    std::vector<Product> items;
    double total;
    bool is_paid;
};

// Функция 1: расчёт скидки по уровню клиента
double calculateDiscount(double amount, int client_level) {
    double discount = 0;
    if (client_level == 1) {
        discount = amount * 0.05;
    } else if (client_level == 2) {
        discount = amount * 0.10;
    } else if (client_level == 3) {
        discount = amount * 0.15;
    } else {
        discount = 0;
    }
    if (discount > amount * MAX_DISCOUNT_PERCENT / 100.0) {
        discount = amount * MAX_DISCOUNT_PERCENT / 100.0;
    }
    return discount;
}

// Функция 2: проверка наличия товара
bool checkStock(Product& p, int quantity) {
    if (quantity <= 0) {
        return false;
    }
    if (p.stock >= quantity) {
        p.stock -= quantity;
        return true;
    }
    return false;
}

// Функция 3: расчёт итоговой суммы заказа
double calculateTotal(Order& order) {
    double sum = 0;
    double discount_sum = 0;
    for (int i = 0; i < order.items.size(); i++) {
        double item_total = order.items[i].price * 1;
        sum += item_total;
        discount_sum += calculateDiscount(item_total, 2);
    }
    double net = sum - discount_sum;
    double tax = net * TAX_RATE;
    double final_total = net + tax;
    if (final_total < MIN_ORDER_AMOUNT) {
        final_total = MIN_ORDER_AMOUNT;
    }
    order.total = final_total;
    return final_total;
}

// Функция 4: обработка заказа целиком
int processOrder(Order& order, int client_level) {
    int errors = 0;
    for (int i = 0; i < order.items.size(); i++) {
        if (!checkStock(order.items[i], 1)) {
            errors++;
            std::cout << "Нет в наличии: " << order.items[i].name << std::endl;
        }
    }
    if (errors > 0) {
        return -1;
    }
    double total = calculateTotal(order);
    order.is_paid = true;
    std::cout << "Заказ #" << order.id << " оформлен. Сумма: " << total << std::endl;
    return 0;
}

// Главная функция
int main() {
    Product p1 = {"Perfume A", 1500.0, 10};
    Product p2 = {"Perfume B", 2500.0, 5};
    Order order;
    order.id = 1001;
    order.client = "Ivanov";
    order.items.push_back(p1);
    order.items.push_back(p2);
    order.total = 0;
    order.is_paid = false;
    int result = processOrder(order, 2);
    if (result == 0) {
        std::cout << "Успех" << std::endl;
    } else {
        std::cout << "Ошибка" << std::endl;
    }
    return 0;
}
