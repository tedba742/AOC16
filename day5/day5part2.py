from itertools import count
from hashlib import md5

door_id = 'uqwqemis'
password = ['_'] * 8  # Use underscores as placeholders for unfilled positions
found_positions = set()  # To track filled positions

for x in count():
    test = door_id + str(x)
    hash_result = md5(test.encode('utf-8')).hexdigest()
    if hash_result[:5] == '00000':
        pos = hash_result[5]  # The potential position from the hash
        
        if pos.isdigit() and 0 <= int(pos) < 8:  # Check if it's a valid position
            pos = int(pos)
            if pos not in found_positions:  # Check if the position is already filled
                char = hash_result[6]  # The character to place in the position
                password[pos] = char
                found_positions.add(pos)
                
                # Print the current state of the password as a simple animation
                print(''.join(password))
                
                # Break the loop if all positions are filled
                if len(found_positions) == 8:
                    break

print("Final password:", ''.join(password))
