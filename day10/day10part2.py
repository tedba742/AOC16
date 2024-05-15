def main():
    bots = {}
    outputs = {}
    instructions = {}

    with open("input.txt", "r") as file:
        for line in file:
            line = line.strip()
            if line.startswith('value'):
                parts = line.split()
                value = int(parts[1])
                bot_id = parts[-1]
                if bot_id not in bots:
                    bots[bot_id] = []
                bots[bot_id].append(value)
            else:
                parts = line.split()
                bot_id = parts[1]
                low_type = parts[5]
                low_id = parts[6]
                high_type = parts[10]
                high_id = parts[11]
                instructions[bot_id] = (low_type, low_id, high_type, high_id)

    while any(len(chips) == 2 for chips in bots.values()):
        for bot_id, chips in list(bots.items()):
            if len(chips) == 2:
                if 61 in chips and 17 in chips:
                    print(f"Bot {bot_id} is responsible for comparing microchip 61 with microchip 17.")
                low_chip, high_chip = sorted(chips)
                low_type, low_id, high_type, high_id = instructions[bot_id]
                
                if low_type == "bot":
                    if low_id not in bots:
                        bots[low_id] = []
                    bots[low_id].append(low_chip)
                else:
                    outputs[low_id] = low_chip

                if high_type == "bot":
                    if high_id not in bots:
                        bots[high_id] = []
                    bots[high_id].append(high_chip)
                else:
                    outputs[high_id] = high_chip
                
                bots[bot_id] = []

    product = outputs.get("0", 1) * outputs.get("1", 1) * outputs.get("2", 1)
    print(f"The product of the values in outputs 0, 1, and 2 is: {product}")

if __name__ == "__main__":
    main()
