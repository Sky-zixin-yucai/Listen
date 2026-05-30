#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

struct Triplet {
    int Q, K, V;
};

struct Earthworm {
    struct Triplet history[100];
    int transition_points[100];
    float phase_threshold;
    int history_index;
};
void initialize_earthworm(struct Earthworm *ew) {
    if (ew == NULL) return;
    memset(ew->history, 0, sizeof(ew->history));
    memset(ew->transition_points, 0, sizeof(ew->transition_points));
    ew->phase_threshold = 0.83f;
    ew->history_index = 0;
    // Additional initialization logic can be added here if necessary
}
int compute_state_change(struct Earthworm *ew, int current_time) {
    if (ew == NULL || current_time <= 0 || current_time >= ew->history_index) return 0;
    int Q_t = ew->history[current_time].Q;
    int K_t = ew->history[current_time].K;
    int V_t = ew->history[current_time].V;
    int Q_t_1 = ew->history[current_time - 1].Q;
    int K_t_1 = ew->history[current_time - 1].K;
    int V_t_1 = ew->history[current_time - 1].V;
    int delta_Q = 0, delta_K = 0, delta_V = 0;
    int norm_type = 2;
    if (norm_type == 2) {
        delta_Q = (Q_t - Q_t_1) * (Q_t - Q_t_1);
        delta_K = (K_t - K_t_1) * (K_t - K_t_1);
        delta_V = (V_t - V_t_1) * (V_t - V_t_1);
    } else if (norm_type == 1) {
        delta_Q = (Q_t - Q_t_1);
        delta_K = (K_t - K_t_1);
        delta_V = (V_t - V_t_1);
    } else {
        printf("Unknown norm type: %d\n", norm_type);
    }
    return delta_Q + delta_K + delta_V;
}
int detect_phase_transition(struct Earthworm *ew, int current_time) {
    if (ew == NULL) return 0;
    int Q_t = 0, K_t = 0, V_t = 0;
    int Q_t_1 = 0, K_t_1 = 0, V_t_1 = 0;
    int delta_Q = 0, delta_K = 0, delta_V = 0;
    float delta_total = 0;
    int is_transition = 0;

    if (ew->history_index >= 2) {
        Q_t = ew->history[ew->history_index - 1].Q;
        K_t = ew->history[ew->history_index - 1].K;
        V_t = ew->history[ew->history_index - 1].V;
        Q_t_1 = ew->history[ew->history_index - 2].Q;
        K_t_1 = ew->history[ew->history_index - 2].K;
        V_t_1 = ew->history[ew->history_index - 2].V;
    }

    delta_Q = (Q_t - Q_t_1);
    delta_K = (K_t - K_t_1);
    delta_V = (V_t - V_t_1);

    delta_total = (float)(delta_Q + delta_K + delta_V) / 3.0f;
    is_transition = (delta_total > 0 ? delta_total : -delta_total) > ew->phase_threshold;
    if (is_transition) {
        ew->transition_points[ew->history_index - 1] = 1;
        printf("Phase transition detected.\n");
    } else {
        printf("No phase transition detected.\n");
    }
    return is_transition;
}
void stack_three_networks(struct Earthworm *ew, int *Q_list, int weight) {
    if (Q_list == NULL || ew == NULL) return;
    int shapes[3] = {1, 1, 1};
    if (shapes[0] != shapes[1] || shapes[1] != shapes[2]) {
        printf("Error: All Q values must have the same shape.\n");
        return;
    }
    int weights[3] = {1, 1, 1};
    if (weight != 0) {
        weights[0] = weight;
    }
    int softmax_weights[3] = {1, 1, 1};
    int Q_stacked = 0;
    for (int i = 0; i < 3; i++) {
        Q_stacked += Q_list[i] * softmax_weights[i];
    }
}
void apply_one_way_value(struct Earthworm *ew, int hin_in, const char *mode, int gate_value) {
    if (strcmp(mode, "detach") == 0) {
        // Placeholder for detach logic
        printf("Applying one Wey value with detach mode.\n");
    } else if (strcmp(mode, "gate") == 0) {
        // Placeholder for gate logic using gate_value
        printf("Applying one Wey value with gate mode.\n");
    } else {
        printf("Unknown mode: %s\n", mode);
    }
    
}

void record_state(struct Earthworm *ew, int Q, int K, int V) {
    if (ew == NULL) return;
    if (ew->history_index < 100) {
        ew->history[ew->history_index].Q = Q;
        ew->history[ew->history_index].K = K;
        ew->history[ew->history_index].V = V;
        ew->history_index++;
    }
}
void get_state_history(struct Earthworm *ew, int norm_type) {
    if (ew == NULL || norm_type == 2) return;
    for (int i = 1; i < ew->history_index; i++) {
        compute_state_change(ew, i);
    }
    printf("State history retrieved with norm type %d.\n", norm_type);
}

void analyze_learning_phases(struct Earthworm *ew) {
    int changes[100] = {0};
    if (ew != NULL) {
        get_state_history(ew, 1);
        int start = (ew->history_index > 5) ? ew->history_index - 5 : 0;
        for (int i = start; i < ew->history_index; i++) {
            if (i > 0) {
                changes[i] = (ew->history[i].Q - ew->history[i-1].Q) +
                             (ew->history[i].K - ew->history[i-1].K) +
                             (ew->history[i].V - ew->history[i-1].V);
            }
        }
    }

    float avg_change = 0.0f;
    int count = 0;
    int start = (ew->history_index > 5) ? ew->history_index - 5 : 0;
    for (int i = start; i < ew->history_index && i < 100; i++) {
        if (changes[i] != 0) {
            avg_change += changes[i];
            count++;
        }
    }
    if (count > 0) {
        avg_change /= count;
    }
    if (avg_change > 25) {
        printf("High learning phase detected.\n");
    } else if (avg_change > 15) {
        printf("Medium learning phase detected.\n");
    } else if (avg_change > 5) {
        printf("Low learning phase detected.\n");
    } else {
        printf("Stable learning phase detected.\n");
    }
}
void reset(struct Earthworm *ew) {
    if (ew == NULL) return;
    memset(ew->history, 0, sizeof(ew->history));
    memset(ew->transition_points, 0, sizeof(ew->transition_points));
    ew->phase_threshold = 0.83f;
    ew->history_index = 0;
}

void get_transition_summary(struct Earthworm *ew) {
    if (ew == NULL) return;
    int total_transitions = 0;
    for (int i = 0; i < 100; i++) {
        if (ew->transition_points[i] != 0) {
            total_transitions++;
        }
    }
    printf("Total transitions detected: %d\n", total_transitions);

}
bool validate_earthworm(const struct Earthworm *ew) {
    if (ew == NULL) return false;
    if (ew->phase_threshold < 0.0f || ew->phase_threshold > 1.0f) {
        printf("Invalid phase threshold: %.2f\n", ew->phase_threshold);
        return false;
    }
    if (ew->history_index < 0 || ew->history_index > 100) {
        printf("Invalid history index: %d\n", ew->history_index);
        return false;
    }
    return 0;
}