.section .text
.global read_keys_asm
.type read_keys_asm, %function
read_keys_asm:
    ldr r0, =0x04000130  // Load address of KEY_INPUT
    ldr r0, [r0]         // Load value from KEY_INPUT
    mvn r0, r0           // Invert the bits
    ldr r1, =0x3FF       // Load the mask value into r1
    and r0, r0, r1       // Apply mask
    bx lr                // Return