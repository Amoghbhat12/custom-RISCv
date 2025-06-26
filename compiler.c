#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

// Register mapping: R0 - R7
int get_register(const char *reg) {
    if (reg[0] != 'R' && reg[0] != 'r') return -1;
    int num = atoi(&reg[1]);
    if (num < 0 || num > 7) return -1;
    return num;
}

// Instruction encoders
uint32_t encode_ADD(int rd, int rs1, int rs2) {
    return 0x01 << 24 | (rd << 20) | (rs1 << 16) | (rs2 << 12);
}

uint32_t encode_SUI(int rd, int rs1, int imm) {
    return 0x91 << 24 | (rd << 20) | (rs1 << 16) | (imm & 0xFF);
}

uint32_t encode_MOV(int rd, int rs) {
    return 0x42 << 24 | (rd << 20) | (rs << 16);
}

uint32_t encode_MVI(int rd, int imm) {
    return 0x72 << 24 | (rd << 20) | (imm & 0xFF);
}

uint32_t encode_HLT() {
    return 0xC0 << 24;
}

uint32_t encode_LOAD(int rd, int rs1, int imm) {
    return 0x51 << 24 | (rd << 20) | (rs1 << 16) | (imm & 0xFF);
}

uint32_t encode_STORE(int rs2, int rs1, int imm) {
    return 0x63 << 24 | (rs2 << 20) | (rs1 << 16) | (imm & 0xFF);
}

// Main parser
void parse_and_encode(FILE *input, FILE *output) {
    char line[256];
    while (fgets(line, sizeof(line), input)) {
        char op[10], rd_str[10], rs1_str[10], rs2_str[10];
        int rd, rs1, rs2, imm;
        uint32_t bin = 0;
        int matched = 0;

        if (sscanf(line, "ADD %[^,], %[^,], %[^,\n]", rd_str, rs1_str, rs2_str) == 3) {
            rd = get_register(rd_str);
            rs1 = get_register(rs1_str);
            rs2 = get_register(rs2_str);
            bin = encode_ADD(rd, rs1, rs2);
            matched = 1;
        } else if (sscanf(line, "SUI %[^,], %[^,], %d", rd_str, rs1_str, &imm) == 3) {
            rd = get_register(rd_str);
            rs1 = get_register(rs1_str);
            bin = encode_SUI(rd, rs1, imm);
            matched = 1;
        } else if (sscanf(line, "MOV %[^,], %[^,\n]", rd_str, rs1_str) == 2) {
            rd = get_register(rd_str);
            rs1 = get_register(rs1_str);
            bin = encode_MOV(rd, rs1);
            matched = 1;
        } else if (sscanf(line, "MVI %[^,], %d", rd_str, &imm) == 2) {
            rd = get_register(rd_str);
            bin = encode_MVI(rd, imm);
            matched = 1;
        } else if (strncmp(line, "HLT", 3) == 0) {
            bin = encode_HLT();
            matched = 1;
        } else if (sscanf(line, "LOAD %[^,], %[^,], %d", rd_str, rs1_str, &imm) == 3) {
            rd = get_register(rd_str);
            rs1 = get_register(rs1_str);
            bin = encode_LOAD(rd, rs1, imm);
            matched = 1;
        } else if (sscanf(line, "STORE %[^,], %[^,], %d", rs2_str, rs1_str, &imm) == 3) {
            rs2 = get_register(rs2_str);
            rs1 = get_register(rs1_str);
            bin = encode_STORE(rs2, rs1, imm);
            matched = 1;
        }

        if (matched) {
            fprintf(output, "%08X\n", bin);
        } else {
            fprintf(stderr, "Unknown or malformed instruction: %s", line);
        }
    }
}

// Main
int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <input.asm> <output.hex>\n", argv[0]);
        return 1;
    }

    FILE *input = fopen(argv[1], "r");
    if (!input) {
        perror("Error opening input file");
        return 1;
    }

    FILE *output = fopen(argv[2], "w");
    if (!output) {
        perror("Error opening output file");
        fclose(input);
        return 1;
    }

    parse_and_encode(input, output);

    fclose(input);
    fclose(output);
    return 0;
}
