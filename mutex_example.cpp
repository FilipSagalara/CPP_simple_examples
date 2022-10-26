#include <csignal>
#include <iostream>
#include <string>
#include <thread>
#include <random>
#include <vector>
#include <queue>
#include <numeric>
#include <chrono>
#include <ctime>
#include <mutex>

class HumiditySensor {
public:
    HumiditySensor() {
        rng_.seed(static_cast<unsigned int>(std::time(nullptr)));
    }

    double blocking_read() {
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        return dist_(rng_);
    }
private:
    std::mt19937 rng_;
    std::normal_distribution<double> dist_{ 40.0, 10.0 };
};

class Filter {
public:
    Filter(size_t buffer_length = 10) : buffer_length_(buffer_length) {
        buffer_.reserve(buffer_length);
    }
    void add_data(double data) {
        if (buffer_.size() < buffer_length_) {
            buffer_.push_back(data);
        }
        else {
            buffer_[buffer_idx_] = data;
            buffer_idx_ = (buffer_idx_ + 1) % buffer_length_;
        }
    }
    double output() {
        return std::accumulate(buffer_.begin(), buffer_.end(), 0.0) / buffer_.size();
    }
private:
    std::vector<double> buffer_;
    size_t buffer_idx_ = 0;
    size_t buffer_length_;
};

void sensor_thread_func(bool& cont, std::queue<double>& raw_data, std::mutex &mtx_raw) {
    HumiditySensor sensor;
    double a = 0;
    while (cont) {
        a = sensor.blocking_read();
        mtx_raw.lock();
        raw_data.push(a);
        mtx_raw.unlock();
    }

}

void filter_thread_func(bool& cont, std::queue<double>& raw_data, std::vector<double>& filtered_data, std::mutex &mtx_raw, std::mutex &mtx_filtered) {
    Filter filter;
   
    while (cont) {
        std::this_thread::sleep_for(std::chrono::seconds(1));

        mtx_raw.lock();
        while (!raw_data.empty()) {
            filter.add_data(raw_data.back());
            
            raw_data.pop();
        }
        mtx_raw.unlock();
        mtx_filtered.lock();
        filtered_data.push_back(filter.output());
        mtx_filtered.unlock();
    }
   
}

bool cont = true;

int main() {

    std::mutex mtx_raw;
    std::mutex mtx_filtered;

    std::signal(SIGINT, [](int) {std::cout << "Quitting"; cont = false; });

    std::queue<double> raw_data_;
    std::vector<double> filtered_data_;

    std::thread sensor_thread(sensor_thread_func, std::ref(cont), std::ref(raw_data_), std::ref(mtx_raw));
    std::thread filter_thread(filter_thread_func, std::ref(cont), std::ref(raw_data_), std::ref(filtered_data_), std::ref(mtx_raw), std::ref(mtx_filtered));

    while (cont) {
        mtx_filtered.lock();
        if (!filtered_data_.empty()) {
            std::cout << "filtered data:";
            for (double v : filtered_data_) {
                std::cout << " " << v;
            }
            std::cout << std::endl;
            filtered_data_.clear();
        }
        mtx_filtered.unlock();
        std::this_thread::sleep_for(std::chrono::seconds(3));
    }
    sensor_thread.join();
    filter_thread.join();
}