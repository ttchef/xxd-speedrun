## Cheesecake Review

FUNCTIONALITY (8/10)
 * -1 for printing it not lower-case like xdd does
 * -1 for printing it without color

CODE (4/10)
 * -1 for char
 * -1 for fgets
 * -2 for print_line
 * -1 for wrong modulos
 * -1 for vla on the stack
also minor issues that i won't deduct points for as it would be a 0/10:
 * magic number 16
 * print_line has side effects
 * pattern-matching is not abstracted so the main loop is kinda hard to follow
 * a lot of typos

BONUS FEATURE (7.5/10)
 * -1 for having to input a file
 * -1 for weird arg parsing
 * -0.5 for using carets (could have just colored it instead)

19.5/30

## ⚡ xxd.c — a Hexdump Utility From the Near Future

> “In the future, everything is bytes.  
> This tool just shows you the truth.”

## 🧬 What Is This?

**xxd.c** is a clean-room, zero-bloat clone of `xxd` written in pure C.  
No dependencies. No fluff. Just raw bytes rendered into human-readable form.

Think of it as:

- a forensic visor for binary files  
- a debugging exoskeleton for your terminal  
- a byte-level telescope aimed straight at the void  

If your file exists, `xxd.c` will decode its soul.

## 🚀 Features

- 🧠 Classic hexdump format (offsets, hex bytes, ASCII mirror)
- ⚙️ Pure C implementation — portable, hackable, immortal
- 🧊 Deterministic output — same bytes, same truth, every time
- 🛰️ Stream-friendly — works with files or `stdin`
- 🔬 Byte-accurate — no rounding, no guessing, no mercy

Optional features (depending on your implementation):

- `-g` group bytes
- `-c` custom column widths
- `-r` reverse mode (hex → binary)
- `-l` limit output size

## 🧪 Example Output


