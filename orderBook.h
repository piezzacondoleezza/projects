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

    OrderBook<T>(const std::map<T, uint32_t>& askMap_,
        const std::map<T, uint32_t>& bidMap_) : 
        askMap(askMap_), 
        bidMap(bidMap_) 
        {}
    
    OrderBook<T>(OrderBook<T>&& other) : askMap(std::forward<std::map<T, uint32_t>>(other.askMap)),
                bidMap(std::forward<std::map<T, uint32_t>>(other.bidMap)) {
    }

    OrderBook<T>(const OrderBook<T>& other) : askMap(other.askMap), bidMap(other.bidMap) {
    }

    OrderBook<T>& operator=(const OrderBook<T>& other) {
        askMap = other.askMap;
        bidMap = other.bidMap;
        return *this;
    }

    void UpdateAskPriceAndAmount(T price, uint32_t amount) {
        if (amount == 0) {
            auto iterator = askMap.find(price);
            if (iterator != askMap.end()) {
                askMap.erase(iterator);
            }
        } else {
            askMap[price] = amount;
        }
    }
    
    void UpdateBidPriceAndAmount(T price, uint32_t amount) {
        if (amount == 0) {
            auto iterator = bidMap.find(price);
            if (iterator != bidMap.end()) {
                bidMap.erase(iterator);
            }
        } else {
            bidMap[price] = amount;
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
    std::map<T, uint32_t> askMap;
    std::map<T, uint32_t> bidMap;
};
