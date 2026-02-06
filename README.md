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

