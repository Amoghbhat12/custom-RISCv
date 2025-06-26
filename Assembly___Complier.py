# Python encoder for the 32-bit instruction format described

# Define opcode mappings
opcode_map = {
    "ADD": 0x0, "SUB": 0x1, "AND": 0x2, "OR": 0x3,
    "MOV": 0x4, "LOAD": 0x5, "STORE": 0x6, "MVI": 0x7,
    "ADI": 0x8, "SUI": 0x9, "ANI": 0xA, "ORI": 0xB,
    "HLT": 0xC
}

# Register encoding
register_map = {
    f"R{i}": i for i in range(8)
}

def encode_instruction(instruction):
    parts = instruction.replace(",", "").split()
    opcode_str = parts[0].upper()
    opcode = opcode_map[opcode_str]

    # Defaults
    ry = ra = rb = imm = 0

    if opcode_str == "HLT":
        pass  # all values remain zero
    elif opcode_str in {"ADD", "SUB", "AND", "OR"}:
        ry = register_map[parts[1]]
        ra = register_map[parts[2]]
        rb = register_map[parts[3]]
    elif opcode_str == "MOV":
        ry = register_map[parts[1]]
        ra = register_map[parts[2]]
    elif opcode_str in {"LOAD", "STORE"}:
        ry = register_map[parts[1]]
        ra = register_map[parts[2]]
        imm = int(parts[3]) & 0xFFFF
    elif opcode_str in {"MVI"}:
        ry = register_map[parts[1]]
        imm = int(parts[2]) & 0xFFFF
    elif opcode_str in {"ADI", "SUI", "ANI", "ORI"}:
        ry = register_map[parts[1]]
        ra = register_map[parts[2]]
        imm = int(parts[3]) & 0xFFFF

    # Construct the instruction (32-bit)
    encoded = (opcode << 28) | (ry << 24) | (ra << 20) | (rb << 16) | imm
    return f"{encoded:08X}"

# Test the encoder with a few sample instructions
test_instructions = [
    "ADD R1, R2, R2",
    "SUI R1, R2, 200",
    "MOV R2, R6",
    "MVI R2, 240",
    "HLT",
    "LOAD R1, R2, 12",
    "STORE R3, R4, 20"
]

# Encode all test instructions
encoded_instructions = {inst: encode_instruction(inst) for inst in test_instructions}
encoded_instructions
