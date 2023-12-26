#include <iostream>
#include <random>

using namespace std;

namespace algorithm {

	struct stats {
		size_t comparison_count = 0;
		size_t copy_count = 0;
		stats() : comparison_count(0), copy_count(0) {}
		stats(const stats& other) {
			comparison_count = other.comparison_count;
			copy_count = other.copy_count;
		}
		stats& operator=(const stats& other) {
			comparison_count = other.comparison_count;
			copy_count = other.copy_count;
		}
	};

	void swap(int& a, int& b, stats& stats) {
		int temp = a;
		a = b;
		b = temp;
		stats.copy_count += 3;
	}

	template<typename T>
	stats insert_sort(vector<T>& arr) {
		stats cur_stat;
		for (int i = 1; i < arr.size(); i++) {
			cur_stat.comparison_count++;
			for (int j = i; j > 0 && arr[j - 1] > arr[j]; j--) {
				cur_stat.copy_count++;
				std::swap(arr[j - 1], arr[j]);
			}
		}
		return cur_stat;
	}

	}
	int partition(std::vector<int>& arr, int low, int high, stats& stats) {
		int pivot = arr[high];
		int i = (low - 1);
		for (int j = low; j <= high - 1; j++) {
			if (arr[j] <= pivot) {
				i++;
				swap(arr[i], arr[j], stats);
			}
			stats.comparison_count++;
		}
		swap(arr[i + 1], arr[high], stats);
		return (i + 1);
	}

	stats quickSort(std::vector<int>& arr, int low, int high) {
		stats stat;
		if (low < high) {
			int pi = partition(arr, low, high, stat);
			stats left_stats = quickSort(arr, low, pi - 1);
			stats right_stats = quickSort(arr, pi + 1, high);
			stat.comparison_count+= left_stats.comparison_count + right_stats.comparison_count;
			stat.copy_count += left_stats.copy_count + right_stats.copy_count;
		}
		return stat;
	}
	template<typename T>
	std::ostream& operator << (std::ostream& os, const std::vector<T> vec) {
		os << "{ ";
		for (int i = 0; i < vec.size(); i++) {
			if (i < vec.size() - 1)
				os << vec[i] << ", ";
			else {
				os << vec[i] << " }" << endl;
			}
		}
		return os;
	}
	std::ostream& operator <<(std::ostream& os, const stats description) {
		os << "Compasion count: " << description.comparison_count << "; " << "Copy count: " << description.copy_count << endl;
		return os;
	}
}