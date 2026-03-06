#ifndef GOLD_H // 防止重复包含
#define GOLD_H // 定义 RGA 模型的结构和相关函数

#include <stddef.h> // 包含标准定义库
#include <stdio.h> // 包含标准输入输出库
#include <string.h> // 包含字符串处理库
#include <stdlib.h> // 包含标准库
#include <stdbool.h> // 包含布尔类型支持

// 这个文件定义了 RGA 模型的结构和相关函数，用于初始化和验证 RGA 配置
struct Rga_gold {
    int Rga_Quantity; // 词汇表大小
    int Rga_Dimension; // 向量维度
    int Rga_NumUnits; // 单元数量
    int Rga_GeoDepth; // 几何深度
    int Rga_MaxCycles; // 最大循环次数
    float Rga_PhaseThreshold; // 阶段转换阈值
    float Rga_VScalingFactor; // V 值缩放因子
    float Rga_MinQConfidence; // 最小 Q 置信度
    int Rga_HistoryLength; // 历史记录长度
    char Rga_DensityMethod[20]; // 密度方法
};

void initialize_rga(struct Rga_gold* rga); // 初始化 RGA 模型的默认配置
void validate_rga_config(struct Rga_gold* rga); // 验证 RGA 配置的有效性，检查各个参数是否在合理范围内

#endif // GOLD_H