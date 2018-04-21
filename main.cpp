#include "Queue.hpp"

int main() {
    Queue <int> q1;
    Queue <int> q2 = {1, 2, 3, 4};
    Queue <int> q3 {q2};
    std::cout << q2 << std::endl;
    std::cout << q3 << std::endl;
    q1.swap(q3);
    std::cout << q1 << std::endl;
    std::cout << boolalpha
    << q3.empty()<< endl;
    std::cout << q1.size() << std::endl;
    q3.push(5);
    std::cout << q3 << std::endl;
    std::ofstream output { "queue.bin" };
    output << q3;
    output.close();
    Queue <int> q4;
    std::ifstream input { "queue.bin" };
    input >> q4;
    input.close();
    std::cout << (q4 == q3) << std::endl;
    std::cout << q4.front() << std::endl;
    std::cout << q4.back() << std::endl;
    q4.pop();
    std::cout << q4 << std::endl;
    q4.front() = 6;
}
