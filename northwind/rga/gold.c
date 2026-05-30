#include <stdio.h> // 包含标准输入输出库
#include <string.h> // 包含字符串处理库
#include <stdlib.h> // 包含标准库
#include <stdbool.h> // 包含布尔类型支持

// 这个文件包含了 RGA 模型的定义和初始化函数
struct Rga_gold {
    int Rga_Quantity;  // 词汇表大小
    int Rga_Dimension;  // 向量维度
    int Rga_NumUnits;  // 单元数量
    int Rga_GeoDepth;  // 几何深度
    int Rga_MaxCycles;  // 最大循环次数
    float Rga_PhaseThreshold;  // 阶段转换阈值
    float Rga_VScalingFactor;  // V 值缩放因子
    float Rga_MinQConfidence;  // 最小 Q 置信度
    int Rga_HistoryLength;  // 历史记录长度
    char Rga_DensityMethod[20];  // 密度方法（如 "uniform" 或 "normal"）       
    
};

// 初始化 RGA 模型的默认配置
void initialize_rga(struct Rga_gold* rga) {
    rga->Rga_Quantity = 10000; // 默认词汇表大小
    rga->Rga_Dimension = 32; // 默认向量维度
    rga->Rga_NumUnits = 3; // 默认单元数量
    rga->Rga_GeoDepth = 3; // 默认几何深度
    rga->Rga_MaxCycles = 10; // 默认最大循环次数
    rga->Rga_PhaseThreshold = 0.83f; // 默认阶段转换阈值
    rga->Rga_VScalingFactor = 1.0f; // 默认 V 值缩放因子
    rga->Rga_MinQConfidence = 0.01f; // 默认最小 Q 置信度
    rga->Rga_HistoryLength = 10; // 默认历史记录长度
    strcpy(rga->Rga_DensityMethod, "uniform"); // 默认密度方法
}

void validate_rga_config(struct Rga_gold* rga) {
    if (rga == NULL) {
        printf("RGA configuration is NULL.\n"); // 验证 RGA 配置是否为 NULL
        return;
    }
    if (rga->Rga_Quantity <= 0) {
        printf("Invalid vocab size: %d\n", rga->Rga_Quantity); // 验证词汇表大小
    }
    if (rga->Rga_Dimension <= 0) {
        printf("Invalid dimension: %d\n", rga->Rga_Dimension); // 验证向量维度
    }
    if (rga->Rga_NumUnits <= 0) {
        printf("Invalid number of units: %d\n", rga->Rga_NumUnits); // 验证单元数量
    }
    if (rga->Rga_GeoDepth <= 0) {
        printf("Invalid geo depth: %d\n", rga->Rga_GeoDepth); // 验证几何深度
    }
    if (rga->Rga_MaxCycles <= 0) {
        printf("Invalid max cycles: %d\n", rga->Rga_MaxCycles); // 验证最大循环次数
    }
    if (rga->Rga_PhaseThreshold < 0.0f || rga->Rga_PhaseThreshold > 1.0f) {
        printf("Invalid phase threshold: %.2f\n", rga->Rga_PhaseThreshold); // 验证阶段转换阈值
    }
    if (rga->Rga_VScalingFactor <= 0.0f) {
        printf("Invalid V scaling factor: %.2f\n", rga->Rga_VScalingFactor); // 验证 V 值缩放因子
    }
    if (rga->Rga_MinQConfidence < 0.0f || rga->Rga_MinQConfidence > 1.0f) {
        printf("Invalid min Q confidence: %.2f\n", rga->Rga_MinQConfidence); // 验证最小 Q 置信度
    }
    if (rga->Rga_HistoryLength <= 0) {
        printf("Invalid history length: %d\n", rga->Rga_HistoryLength); // 验证历史记录长度
    }
    if (strcmp(rga->Rga_DensityMethod, "uniform") != 0 && strcmp(rga->Rga_DensityMethod, "normal") != 0) {
        printf("Invalid density method: %s\n", rga->Rga_DensityMethod); // 验证密度方法
    }
}

int main() {
    struct Rga_gold rga; // 创建 RGA 结构体实例
    initialize_rga(&rga); // 初始化 RGA 配置
    validate_rga_config(&rga); // 验证 RGA 配置
    
    printf("RGA configuration initialized and validated successfully.\n"); // 输出成功消息
    return 0; // 程序结束
}
