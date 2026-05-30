#ifndef EARTHWORM_H
#define EARTHWORM_H

#include <stdbool.h>  // 因为用了 bool

struct Triplet {
    int Q, K, V;
};

struct Earthworm {
    struct Triplet history[100];
    int transition_points[100];
    float phase_threshold;
    int history_index;
};

void initialize_earthworm(struct Earthworm *ew);
int compute_state_change(struct Earthworm *ew, int current_time);
int detect_phase_transition(struct Earthworm *ew, int current_time);
void stack_three_networks(struct Earthworm *ew, int *Q_list, int weight);
void apply_one_way_value(struct Earthworm *ew, int hin_in, const char *mode, int gate_value);
void record_state(struct Earthworm *ew, int Q, int K, int V);
void get_state_history(struct Earthworm *ew, int norm_type);
void analyze_learning_phases(struct Earthworm *ew);
void reset(struct Earthworm *ew);
void get_transition_summary(struct Earthworm *ew);
bool validate_earthworm(const struct Earthworm *ew);

#endif