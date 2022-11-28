#include <cstdio>
#include <cassert>
#include <thread>
#include <mutex>
#include <condition_variable>

/* G1 */

void counter(int n) {
    /* C1 */
    printf("%d\n", n + 1);
    /* C2 */
}

int main() {
    /* M1 */
    std::thread t1(counter, 0);
    std::thread t2(counter, 1);
    std::thread t3(counter, 2);
    /* M2 */
    t3.join();
    t2.join();
    t1.join();
}
