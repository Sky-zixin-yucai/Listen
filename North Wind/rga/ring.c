#include <stdio.h> // 包含标准输入输出库
#include <string.h> // 包含字符串处理库
#include <stdlib.h> // 包含标准库
#include <stdbool.h> // 包含布尔类型支持

struct Status_History {
    int Q;
    int K;
    int V;
};
// 这个文件包括Rga_Knight结构体定义和相关函数实现
struct Rga_Knight {
    int Rga_Q_vocabulary_key; // Q 词汇表键
    int Rga_K_connection_key; // K 连接键
    int Rga_V_relationship_key; // V 关系键
    struct Status_History Status_History[100]; // 历史状态记录
    int Transition_Points[100]; // 转换点记录
    float Phase_Threshold; // 阶段转换阈值
    int History_Index; // 历史记录索引
};

// 初始化 Rga_Knight 结构体的默认值
void initialize_rga_knight(struct Rga_Knight* knight) {
    if (knight == NULL) return; // 检查输入指针是否为 NULL
    knight->Rga_Q_vocabulary_key = 0; // 初始化 Q 词汇表键为 0
    knight->Rga_K_connection_key = 0; // 初始化 K 连接键为 0
    knight->Rga_V_relationship_key = 0; // 初始化 V 关系键为 0
    for (int i = 0; i < 100; i++) {
        knight->Status_History[i].Q = 0; // 初始化历史状态记录的 Q 值为 0
        knight->Status_History[i].K = 0; // 初始化历史状态记录的 K 值为 0
        knight->Status_History[i].V = 0;
        knight->Transition_Points[i] = 0; // 初始化转换点记录为 0
    }
    knight->Phase_Threshold = 0.83f; // 初始化阶段转换阈值为 0.83
    knight->History_Index = 0; // 初始化历史记录索引为 0
}

// 添加一个记录函数，用于记录当前状态到历史中
void record_status(struct Rga_Knight* knight, int Q, int K, int V) {
    if (knight == NULL || knight->History_Index >= 100) return; // 检查输入指针是否为 NULL 或历史记录索引是否超过限制
    knight->Status_History[knight->History_Index].Q = Q; // 记录当前 Q 值
    knight->Status_History[knight->History_Index].K = K; // 记录当前 K 值
    knight->Status_History[knight->History_Index].V = V; // 记录当前 V 值
    knight->History_Index++; // 增加历史记录索引
}

// 其他相关函数的实现可以在这里添加，例如记录状态、检测转换等
void Single_network_variation_formula(struct Rga_Knight* knight, int Internet_formula) {
    if (knight == NULL) return; // 检查输入指针是否为 NULL
    // 这里可以实现单网络变异公式的逻辑
    // 单网络公式：Δ = ||Q_t - Q_{t-1}|| + ||K_t - K_{t-1}|| + ||V_t - V_{t-1}||
    // 具体实现可以根据需要进行调整
    if (knight->History_Index >= 2) {
        int Q_t = knight->Status_History[knight->History_Index - 1].Q; // 获取当前 Q 值
        int K_t = knight->Status_History[knight->History_Index - 1].K; // 获取当前 K 值
        int V_t = knight->Status_History[knight->History_Index - 1].V; // 获取当前 V 值
        int Q_t_1 = knight->Status_History[knight->History_Index - 2].Q; // 获取前一个 Q 值
        int K_t_1 = knight->Status_History[knight->History_Index - 2].K; // 获取前一个 K 值
        int V_t_1 = knight->Status_History[knight->History_Index - 2].V; // 获取前一个 V 值
        int value_Q = 0, value_K = 0, value_V = 0; // 初始化变异值
        if (Internet_formula == 2) {
            // 使用 L2 范数计算变异
            value_Q = (Q_t - Q_t_1) * (Q_t - Q_t_1); // 计算 Q 的 L2 范数变异
            value_K = (K_t - K_t_1) * (K_t - K_t_1); // 计算 K 的 L2 范数变异
            value_V = (V_t - V_t_1) * (V_t - V_t_1); // 计算 V 的 L2 范数变异
        } else if (Internet_formula == 1) {
            // 使用 L1 范数计算变异
            value_Q = abs(Q_t - Q_t_1); // 计算 Q 的 L1 范数变异
            value_K = abs(K_t - K_t_1); // 计算 K 的 L1 范数变异
            value_V = abs(V_t - V_t_1); // 计算 V 的 L1 范数变异
        } else {
            printf("Unknown Internet formula: %d\n", Internet_formula); // 输出未知公式的错误信息
            return;
        }
        int total_variation = value_Q + value_K + value_V; // 计算总变异
        printf("Total variation calculated: %d\n", total_variation); // 输出计算的总变异值
    } if (Internet_formula != 1 && Internet_formula != 2) {
        printf("Unknown Internet formula: %d\n", Internet_formula); // 输出未知公式的错误信息
        return;
    }
}

// 在调用计算前，先设置 Q、K、V 并记录几次状态以确保历史记录有数据
int main() {
    struct Rga_Knight knight; // 创建 Rga_Knight 结构体实例
    initialize_rga_knight(&knight); // 初始化 Rga_Knight 的默认值
    // 添加测试数据
    record_status(&knight, 10, 20, 30); // 记录第一次状态
    record_status(&knight, 15, 25, 35); // 记录第二次状态
    Single_network_variation_formula(&knight, 2); // 调用单网络变异公式，使用 L2 范数
    Single_network_variation_formula(&knight, 1); // 调用单网络变异公式，使用 L1范数
    Single_network_variation_formula(&knight, 3); // 调用单网络变异公式，使用未知公式测试错误处理
    return 0; // 程序结束
}