from itertools import count
from hashlib import md5    

for x in count(8):
    test = 'uqwqemis' + str(x)
    hash_result = md5(test.encode('utf-8')).hexdigest()
    if hash_result[:5] == '00000':
        print("Sixth character of the hash:", hash_result[5])
