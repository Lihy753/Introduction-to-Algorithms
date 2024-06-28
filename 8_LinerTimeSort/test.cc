#include <iostream>
#include <random>

int main() {
    // 使用随机设备获取种子
    std::random_device rd;
    // 使用随机设备生成器初始化随机数生成器
    std::mt19937 gen(rd());
    // 设置均匀实数分布器在 [0, 1) 内
    std::uniform_real_distribution<float> dis(0.0f, 1.0f);

    // 生成随机数
    float random_number = dis(gen);

    // 输出生成的随机数
    std::cout << "random: " << random_number << std::endl;

    return 0;
}
