from itertools import count
from hashlib import md5

door_id = 'uqwqemis'
password = ['_'] * 8
found_positions = set()

for x in count():
    test = door_id + str(x)
    hash_result = md5(test.encode('utf-8')).hexdigest()
    if hash_result[:5] == '00000':
        pos = hash_result[5]
        
        if pos.isdigit() and 0 <= int(pos) < 8:
            pos = int(pos)
            if pos not in found_positions:
                char = hash_result[6]
                password[pos] = char
                found_positions.add(pos)
                
                print(''.join(password))
                
                if len(found_positions) == 8:
                    break

print("Final password:", ''.join(password))
