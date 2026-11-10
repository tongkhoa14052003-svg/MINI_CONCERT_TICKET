
#ifndef SEARCH_HISTORY_H
#define SEARCH_HISTORY_H

#include <string>
#include <vector>

class SearchHistory {
private:
    struct HistoryNode {
        std::string keyword;
        HistoryNode* next;

        explicit HistoryNode(const std::string& value);
    };

    HistoryNode* head;
    int count;
    int maxSize;

public:
    explicit SearchHistory(int limit = 10);
    ~SearchHistory();

    SearchHistory(const SearchHistory&) = delete;
    SearchHistory& operator=(const SearchHistory&) = delete;

    void recordSearch(const std::string& keyword);
    std::vector<std::string> getHistory() const;

    void display() const;
    int size() const;
    void clear();
};

#endif
