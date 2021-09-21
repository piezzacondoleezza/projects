#include "orderBook.h"
#include <exception>
#include <initializer_list>


void Check(std::initializer_list<bool> lst) {
    for (auto it : lst) {
        if (!it) {
            throw std::exception();
        }
    }
}

void Test1() {
    OrderBook<int> orderBook;

    orderBook.UpdateAskPriceAndAmount(4, 5);
    auto [bid, ask] = orderBook.GetTopBidAskOfTheBookWithoutAmount();
    Check({!bid.has_value(), *ask == 4});

    orderBook.UpdateAskPriceAndAmount(4, 0);
    tie(bid, ask) = orderBook.GetTopBidAskOfTheBookWithoutAmount();
    Check({!bid.has_value(), !ask.has_value()});

    orderBook.UpdateBidPriceAndAmount(5, 2);
    tie(bid, ask) = orderBook.GetTopBidAskOfTheBookWithoutAmount();
    Check({*bid == 5, !ask.has_value()});

    orderBook.UpdateBidPriceAndAmount(5, 0);
    tie(bid, ask) = orderBook.GetTopBidAskOfTheBookWithoutAmount();
    Check({!bid.has_value(), !ask.has_value()});

    orderBook.UpdateBidPriceAndAmount(5, 2);
    orderBook.UpdateAskPriceAndAmount(7, 5);
    orderBook.UpdateAskPriceAndAmount(5, 4);
    orderBook.UpdateBidPriceAndAmount(4, 3);
    auto [bidBig, askBig] = orderBook.GetTopBidAskOfTheBook();
    Check({bidBig->price == 5, bidBig->amount == 2, askBig->price == 5, askBig->amount == 4});
}

void Test2() {
    OrderBook<int> orderBook;

    orderBook.UpdateAskPriceAndAmount(5, 5);
    orderBook.UpdateAskPriceAndAmount(6, 228);
    OrderBook<int> snapshot = orderBook;
    orderBook.UpdateBidPriceAndAmount(3, 27);
    orderBook.UpdateBidPriceAndAmount(2, 77);
    auto [bidBig, askBig] = orderBook.GetTopBidAskOfTheBook();
    Check({bidBig->price == 3, bidBig->amount == 27, askBig->price == 5, askBig->amount == 5});

    orderBook.UpdateTheBookFromSnapshot(snapshot);
    tie(bidBig, askBig) = orderBook.GetTopBidAskOfTheBook();
    Check({!bidBig.has_value(), askBig->price == 5, askBig->amount == 5});

    orderBook.UpdateTheBookFromSnapshot(OrderBook<int>());
    tie(bidBig, askBig) = orderBook.GetTopBidAskOfTheBook();
    Check({!bidBig.has_value(), !askBig.has_value()});
}

void Test3() {
    OrderBook<int> orderBook;
    
    orderBook.UpdateAskPriceAndAmount(5, 36);
    orderBook.UpdateAskPriceAndAmount(6, 228);
    orderBook.UpdateBidPriceAndAmount(3, 27);
    orderBook.UpdateBidPriceAndAmount(2, 77);
    orderBook.UpdateBidPriceAndAmount(2, 0);
    orderBook.UpdateBidPriceAndAmount(3, 0);
    auto [bidBig, askBig] = orderBook.GetTopBidAskOfTheBook();
    Check({!bidBig.has_value(), askBig->price == 5, askBig->amount == 36});

    orderBook.UpdateBidPriceAndAmount(2, 77);
    orderBook.UpdateBidPriceAndAmount(2, 0);
    orderBook.UpdateBidPriceAndAmount(17, 223);
    orderBook.UpdateAskPriceAndAmount(5, 0);
    orderBook.UpdateAskPriceAndAmount(7, 48);
    tie(bidBig, askBig) = orderBook.GetTopBidAskOfTheBook();
    Check({bidBig->price == 17, bidBig->amount == 223, askBig->price == 6, askBig->amount == 228});
}


int main() {
    try {
        Test1();
        std::cout << "Test 1 finished succesfull" << std::endl;
    } catch (...) {
        std::cout << "Test 1 failed" << std::endl;
    }
    try {
        Test2();
        std::cout << "Test 2 finished succesfull" << std::endl;
    } catch (...) {
        std::cout << "Test 2 failed" << std::endl;
    }
    try {
        Test3();
        std::cout << "Test 3 finished succesfull" << std::endl;
    } catch (...) {
        std::cout << "Test 3 failed" << std::endl;
    }
    return 0;
}