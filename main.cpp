#include "proj.h"
#include <_types/_uint32_t.h>
#include <cstdint>
#include <exception>
#include <iostream>
#include <string>




template<typename T>
void PrintOptionalPair(std::string streamWord, std::optional<Params<T>> value) {
    std::cout << streamWord << "price = ";
    if (value) {
        std::cout << value->price << ", amount =" << value->amount << std::endl;
    } else {
        std::cout << "does not exist" << std::endl;
    }
}

template<typename T>
void PrintOptionalValue(std::string streamWord, std::optional<T> value) {
    std::cout << streamWord << "price = ";
    if (value) {
        std::cout << *value << std::endl;
    } else {
        std::cout << "does not exist" << std::endl;
    }
}


int main(int argc, char** argv) {
    try {
        OrderBook<double> orderBook;
        int id = 1;
        while (id < argc) {
            std::string cur = argv[id];
            if (cur == "GetTopBidAskOfTheBook") {
                auto [bid, ask] = orderBook.GetTopBidAskOfTheBook();
                PrintOptionalPair<double>("top bid: ", bid);
                PrintOptionalPair<double>("lowest ask: ", ask);
            } else if (cur == "GetTopBidAskOfTheBookWithoutAmount") {
                auto [bid, ask] = orderBook.GetTopBidAskOfTheBookWithoutAmount();
                PrintOptionalValue<double>("top bid", bid);
                PrintOptionalValue<double>("lowest ask", ask);
            } else if (cur == "UpdateAskPriceAndAmount") {
                if (id + 2 >= argc) {
                    throw std::exception();
                }
                double price = std::stod(argv[id + 1]);
                uint32_t amount = std::stoull(argv[id + 2]);
                id += 2;
                orderBook.UpdateAskPriceAndAmount(price, amount);
            } else if (cur == "UpdateBidPriceAndAmount") {
                if (id + 2 >= argc) {
                    throw std::exception();
                }
                double price = std::stod(argv[id + 1]);
                uint32_t amount = std::stoull(argv[id + 2]);
                id += 2;
                orderBook.UpdateBidPriceAndAmount(price, amount);
            } else if (cur == "UpdateTheBookFromSnapshot") {
                //...
            }
            ++id;
        }
    } catch (...) {
        std::cerr << "Oops something went wrong" << std::endl;
    }
    
	return 0;
}
