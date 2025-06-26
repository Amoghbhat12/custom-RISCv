# RISC-V CPU Simulator in logisim

A custom-built 32-bit RISC-V-like CPU simulator written in C. It models instruction execution, memory management, and stage-based control logic. Designed as an educational tool for understanding CPU internals and microarchitecture.

---

## 🚀 Features

- 🧮 **Custom Instruction Set** (13 total)
  - **Data Transfer**: `MOVE`, `LOAD`, `STORE`
  - **Arithmetic**: `ADD`, `SUB`, `ADI` (Add Immediate), `SUI` (Subtract Immediate)
  - **Logic**: `AND`, `ANI`, `OR`, `ORI`
  - **Control**: `HLT` (Halt)

- 🔧 **Registers**
  - **General Purpose**: `R0–R7` (8 total)
  - **Special Purpose**: `PC`, `IR`, `RA`, `RB`, `RM`, `RZ`, `RY`
  

- 📦 **Cycles**
  - The Processor follows a typical 5-stage pipeline with Fetch, Decode, Execute, Memory, and Write Back stages.


- 📦 **Memory**
  - 16-bit address × 32-bit data RAM
  - Memory muxing for instruction vs. data access

- ✅ **Custom Instruction Format**
  - 32-bit format with opcode, destination, source, and immediate fields

---

### Field Descriptions

| Component     | Bits Used     | Description                |
|---------------|---------------|----------------------------|
| **OPCODE**    | 4 bits (31–28) | Operation code             |
| **DEST (RY)** | 5 bits (27–23) | Destination register       |
| **SRC1 (RA)** | 5 bits (22–18) | Source register 1          |
| **SRC2 (RB)** | 5 bits (17–13) | Source register 2          |
| **IMMEDIATE** | 13 bits (12–0) | Immediate value (optional) |

## 📘 Instruction Set & Opcodes

The simulator supports the following 13 custom instructions. Each instruction is uniquely identified using a 4-bit opcode.

### 🧮 Opcodes

| Binary | Hex | Instruction Syntax      | Description                        |
|--------|-----|--------------------------|------------------------------------|
| 0000   | 0   | `ADD Ri, Rj, Rk`         | Ri ← Rj + Rk                       |
| 0001   | 1   | `SUB Ri, Rj, Rk`         | Ri ← Rj - Rk                       |
| 0010   | 2   | `AND Ri, Rj, Rk`         | Ri ← Rj & Rk                       |
| 0011   | 3   | `OR Ri, Rj, Rk`          | Ri ← Rj | Rk                       |
| 0100   | 4   | `MOV Ri, Rj`             | Ri ← Rj                            |
| 0101   | 5   | `LOAD Ri, Rj, X`         | Ri ← MEM[Rj + X]                   |
| 0110   | 6   | `STORE Ri, Rj, X`        | MEM[Rj + X] ← Ri                   |
| 0111   | 7   | `MVI Ri, X`              | Ri ← X (Move Immediate)            |
| 1000   | 8   | `ADI Ri, X`              | Ri ← Ri + X (Add Immediate)        |
| 1001   | 9   | `SUI Ri, X`              | Ri ← Ri - X (Subtract Immediate)   |
| 1010   | A   | `ANI Ri, X`              | Ri ← Ri & X (AND Immediate)        |
| 1011   | B   | `ORI Ri, X`              | Ri ← Ri | X (OR Immediate)         |
| 1100   | C   | `HLT`                    | Halt execution                     |
