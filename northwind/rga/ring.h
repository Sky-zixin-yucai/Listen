#ifndef RING_H
#define RING_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

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
void initialize_rga_knight(struct Rga_Knight* knight);
void record_status(struct Rga_Knight* knight, int Q, int K, int V);
void Single_network_variation_formula(struct Rga_Knight* knight, int Internet_formula);
#endif // RING_H