#include <_types/_uint32_t.h>
#include <iostream>
#include <vector>
#include <map>
#include <utility>
#include <optional>
#include <tuple>

template<class T>
class Params {
public:
    T price;
    uint32_t amount;

    Params() = default;

    Params(std::pair<T, uint32_t> argument_) {
        std::tie(price, amount) = argument_;
    }

    Params& operator=(std::pair<T, uint32_t> argument_) {
        price = argument_.first;
        amount = argument_.second;
        return *this;
    } 
};

template<class T>
class OrderBook {
public:
    OrderBook<T>() = default;

    OrderBook<T>(const std::map<T, int>& askMap_,
        const std::map<T, int>& bidMap_) : 
        askMap(askMap_), 
        bidMap(bidMap_) 
        {}
    
    OrderBook<T>(OrderBook<T>&& other) {
        askMap = other.orderMap;
        bidMap = other.bidMap;
    }

    OrderBook<T>(const OrderBook<T>& other) {
        askMap = other.askMap;
        bidMap = other.bidMap;
    }

    OrderBook<T>& operator=(const OrderBook<T>& other) {
        askMap = other.askMap;
        bidMap = other.bidMap;
        return *this;
    }

    void UpdateAskPriceAndAmount(T price, uint32_t amount) {
        askMap[price] = amount;
        if (amount == 0) {
            askMap.erase(askMap.find(price));
        }
    }
    
    void UpdateBidPriceAndAmount(T price, uint32_t amount) {
        bidMap[price] = amount;
        if (amount == 0) {
            bidMap.erase(bidMap.find(price));
        }
    }

    void UpdateTheBookFromSnapshot(const OrderBook<T>& other) {
        *this = other;
    }

    std::pair<std::optional<Params<T>>, std::optional<Params<T>>> GetTopBidAskOfTheBook() const noexcept {
        std::optional<Params<T>> topAsk, topBid;
        if (bidMap.rbegin() != bidMap.rend())
            topBid = *bidMap.rbegin();
        if (askMap.begin() != askMap.end())
            topAsk = *askMap.begin();
        return std::make_pair(topBid, topAsk);
    }

    std::pair<std::optional<T>, std::optional<T>> GetTopBidAskOfTheBookWithoutAmount() const noexcept {
        std::optional<T> topAsk, topBid;
        if (bidMap.rbegin() != bidMap.rend())
            topBid = bidMap.rbegin()->first;
        if (askMap.begin() != askMap.end())
            topAsk = askMap.begin()->first;
        return std::make_pair(topBid, topAsk);
    }

private:
    std::map<T, int> askMap;
    std::map<T, int> bidMap;
};