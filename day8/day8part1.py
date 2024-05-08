def initialize_display(width, height):
    return [[False] * width for _ in range(height)]

def execute_instruction(display, instruction):
    if instruction.startswith("rect"):
        a, b = map(int, instruction[5:].split("x"))
        for i in range(b):
            for j in range(a):
                display[i][j] = True
    elif instruction.startswith("rotate row"):
        parts = instruction.split()
        row = int(parts[2].split("=")[1])
        amount = int(parts[4])
        display[row] = display[row][-amount:] + display[row][:-amount]
    elif instruction.startswith("rotate column"):
        parts = instruction.split()
        col = int(parts[2].split("=")[1])
        amount = int(parts[4])
        temp = [display[i][col] for i in range(len(display))]
        for i in range(len(display)):
            display[(i + amount) % len(display)][col] = temp[i]

def count_lit_pixels(display):
    return sum(sum(1 for pixel in row if pixel) for row in display)

def read_instructions(file_path):
    with open(file_path, 'r') as file:
        return [line.strip() for line in file]

display = initialize_display(50, 6)

instructions = read_instructions("input.txt")

for instruction in instructions:
    execute_instruction(display, instruction)

lit_count = count_lit_pixels(display)
print("Number of lit pixels:", lit_count)
