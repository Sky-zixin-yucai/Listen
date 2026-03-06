#include <stdio.h>
#include "Earthworm.h"

void test_default_initialization() {
    struct Earthworm ew;
    initialize_earthworm(&ew);
    if (validate_earthworm(&ew)) {
        printf("Default initialization successful.\n");
        printf("Phase threshold: %.2f\n", ew.phase_threshold);
    } else {
        printf("Default initialization failed.\n");
    }
}

void test_state_change() {
    struct Earthworm ew;
    initialize_earthworm(&ew);
    
    // Add test data before calling compute_state_change
    record_state(&ew, 10, 20, 30);
    record_state(&ew, 15, 25, 35);
    
    int ret = compute_state_change(&ew, 1);
    if (ret) {
        printf("State change computed successfully.\n");
    } else {
        printf("State change computation failed (return value: %d).\n", ret);
    }
}

void test_phase_transition() {
    struct Earthworm ew;
    initialize_earthworm(&ew);
    
    // Add test data before calling detect_phase_transition
    record_state(&ew, 10, 20, 30);
    record_state(&ew, 15, 25, 35);
    
    int ret = detect_phase_transition(&ew, 100);
    if (ret) {
        printf("Phase transition detected successfully.\n");
    } else {
        printf("Phase transition detection failed (return value: %d).\n", ret);
    }
}

void test_history_and_analysis() {
    struct Earthworm ew;
    initialize_earthworm(&ew);
    
    // Add test data
    record_state(&ew, 10, 20, 30);
    record_state(&ew, 15, 25, 35);
    
    printf("State history:\n");
    get_state_history(&ew, 5);
    printf("Learning phases analysis:\n");
    analyze_learning_phases(&ew);
    printf("Transition summary:\n");
    get_transition_summary(&ew);
}

void test_custom_threshold() {
    struct Earthworm ew;
    initialize_earthworm(&ew);
    ew.phase_threshold = 0.9f;
    
    if (validate_earthworm(&ew)) {
        printf("Custom threshold initialization successful.\n");
        printf("Phase threshold: %.2f\n", ew.phase_threshold);
    } else {
        printf("Custom threshold initialization failed.\n");
    }
    
    // Add test data before calling compute and detect functions
    record_state(&ew, 10, 20, 30);
    record_state(&ew, 15, 25, 35);
    
    int ret = compute_state_change(&ew, 1);
    if (ret) {
        printf("State change computed successfully with custom threshold.\n");
    } else {
        printf("State change computation failed with custom threshold (return value: %d).\n", ret);
    }
    
    ret = detect_phase_transition(&ew, 100);
    if (ret) {
        printf("Phase transition detected successfully with custom threshold.\n");
    } else {
        printf("Phase transition detection failed with custom threshold (return value: %d).\n", ret);
    }
}

int main() {
    test_default_initialization();
    printf("\n");
    test_state_change();
    printf("\n");
    test_phase_transition();
    printf("\n");
    test_history_and_analysis();
    printf("\n");
    test_custom_threshold();
    return 0;
}