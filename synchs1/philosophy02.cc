#include <cstdio>
#include <cassert>
#include <unistd.h>
#include <random>
#include <thread>
#include <mutex>
#include <condition_variable>

static constexpr int K = 8;   // number of stalls

unsigned long long stalls[K];

void wait_until_uncomfortable() {
    // stoic philosophers are always comfortable
}

void poop_into(int stall) {
    stalls[stall] += 1;
}

void user() {
    std::default_random_engine randomness(std::random_device{}());
    std::uniform_int_distribution<int> pick_stall(0, K - 1);

    while (true) {
        wait_until_uncomfortable();
        int preferred_stall = pick_stall(randomness);
        poop_into(preferred_stall);
    }
}

int main() {
    for (size_t i = 0; i != 32; ++i) {
        std::thread t(user);
        t.detach();
    }

    sleep(5);
}
