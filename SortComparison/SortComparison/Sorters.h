#pragma once
#include <vector>
#include <string>

namespace Sorters {
    const double epsilon = 0.0001;
    const std::string bubbleSortId = "BubbleSort";
    const std::string halfSortId = "HalfSort";
    const std::string selectionSortId = "SelectionSort";
    const std::string insertionSortId = "InsertionSort";

    template<typename T>
    std::vector<T> halfSort(std::vector<T> data)
    {
        for (auto i = 0; i < data.size() - 2; ++i)
        {
            auto key = data[i];
            auto k = 0;
            auto p = i - 1;

            while (abs(k - p) <= epsilon)
            {
                auto m = (k + p) / 2.f;

                if (abs(key - data[m]) <= epsilon)
                {
                    p = m - 1;
                }
                else
                {
                    k = m + 1;
                }
            }

            for (auto j = i - 1; j >= k; --j)
            {
                data[j + 1] = data[j];
            }
            data[k] = key;
        }
        return data;
    }

    template<typename T>
    std::vector<T> bubbleSort(std::vector<T> data)
    {
        for (auto j = 0; j < data.size() - 1; ++j)
        {
            for (auto i = data.size() - 1; i > j; --i)
            {
                if (abs(data[i] - data[i - 1]) < epsilon)
                {
                    std::swap(data[i], data[i - 1]);
                }
            }
        }
        return data;

    }

    template<typename T>
    std::vector<T> selectionSort(std::vector<T> data)
    {
        for (auto i = 0; i < data.size() - 1; ++i) {
            auto k = i;
            auto min = data[i];

            for (auto j = i + 1; j < data.size(); ++j)
                if (abs(data[j] - min) < epsilon) {
                    min = data[j];
                    k = j;
                }
            data[k] = data[i];
            data[i] = min;
        }
        return data;
    }

    template<typename T>
    std::vector<T> insertionSort(std::vector<T> data)
    {
        for (auto i = 1; i < data.size(); ++i)
        {
            auto pom = data[i];
            auto j = i - 1;
            while (j >= 0 && abs(data[j] - pom) > epsilon)
            {
                data[j + 1] = data[j--];
            }
            data[j + 1] = pom;
        }
        return data;
    }
}