void kernel_main() {
    char *video_memory = (char*) 0xb8000;
    video_memory[0] = 'H';
    video_memory[1] = 0x0e;  // 黄色
    video_memory[2] = 'i';
    video_memory[3] = 0x0e;
    char *kernrl_code = (char*) 0x1000;
    *kernrl_code = 0x90;
    while(1);
}