
#include "SearchHistory.h"

#include <iostream>

SearchHistory::HistoryNode::HistoryNode(
    const std::string& value
) : keyword(value), next(nullptr) {
}

SearchHistory::SearchHistory(int limit)
    : head(nullptr),
      count(0),
      maxSize(limit > 0 ? limit : 10) {
}

SearchHistory::~SearchHistory() {
    clear();
}

void SearchHistory::recordSearch(
    const std::string& keyword
) {
    if (keyword.empty()) {
        return;
    }

    HistoryNode* previous = nullptr;
    HistoryNode* current = head;

    while (current != nullptr) {
        if (current->keyword == keyword) {
            if (previous != nullptr) {
                previous->next = current->next;
                current->next = head;
                head = current;
            }

            return;
        }

        previous = current;
        current = current->next;
    }

    HistoryNode* newNode = new HistoryNode(keyword);

    newNode->next = head;
    head = newNode;
    ++count;

    if (count > maxSize) {
        HistoryNode* currentNode = head;
        HistoryNode* previousNode = nullptr;

        while (currentNode->next != nullptr) {
            previousNode = currentNode;
            currentNode = currentNode->next;
        }

        if (previousNode != nullptr) {
            previousNode->next = nullptr;
        }

        delete currentNode;
        --count;
    }
}

std::vector<std::string> SearchHistory::getHistory() const {
    std::vector<std::string> result;

    HistoryNode* current = head;

    while (current != nullptr) {
        result.push_back(current->keyword);
        current = current->next;
    }

    return result;
}

void SearchHistory::display() const {
    std::cout << "\nLICH SU TIM KIEM\n";

    HistoryNode* current = head;
    int position = 1;

    while (current != nullptr) {
        std::cout << position << ". "
                  << current->keyword << '\n';

        current = current->next;
        ++position;
    }

    if (head == nullptr) {
        std::cout << "Chua co lich su tim kiem.\n";
    }
}

int SearchHistory::size() const {
    return count;
}

void SearchHistory::clear() {
    HistoryNode* current = head;

    while (current != nullptr) {
        HistoryNode* nextNode = current->next;

        delete current;
        current = nextNode;
    }

    head = nullptr;
    count = 0;
}
