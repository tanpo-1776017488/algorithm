
#homework 13.5 hwang jae hyeon
#hash function(CyclicShiftHashCode)

class Entry:#실질적인 data값
    def __init__(self, k, v):
        self._key = k
        self._value = v
    def __str__(self):
        return str(self._value)
def CyclicShiftHashCode(str_key): # str_key is string 최대한 겹치지 않는 값을 만듦,많이 겹치면 hash만드는 의미가 없음
    mask = (1 << 32)-1 # limit to 32‐bit integers
    h = 0
    for ch in str_key:
        h = (h << 5 & mask) | (h >> 27) # cyclic shift hash code
        h += ord(ch)
    return h

class Bucket(Entry):#얘는 이름 그대로 Entry를 담을 바구니
    def __init__(self):
        self._bucket = [] # implement bucket using list
    
    def _getitem(self, k):
        for item in self._bucket:
            if k == item._key:
                return item._value
        return None

    def _setitem(self, k, v):
        for item in self._bucket:
            if k == item._key:
                item._value = v
        return self._bucket.append(Entry(k, v))
    
    def _delitem(self, k):
        for j in range(len(self._bucket)):
            if k == self._bucket[j]._key:
                self._bucket.pop(j)
                return 1
        return None

    def __len__(self):
        return len(self._bucket)

    def __iter__(self): # provides iterator as generator function
        for item in self._bucket:
            yield item._key

class HashMap_Bucket(Bucket):#얘는 table
    def __init__(self, table_size=11, prm=109345121):
        self._hash_tbl = table_size * [None]
        self._hash_tbl_size = table_size
        self._num_entry = 0
        self._prime = prm

    def _hash_value(self, k):
        return CyclicShiftHashCode(k) % self._prime % self._hash_tbl_size

    def __len__(self):
        return self._num_entry

    def _getitem(self, k):
        hv = self._hash_value(k)
        bucket = self._hash_tbl[hv]
        if bucket is None:
            return None
        item=bucket._getitem(k)
        if item is None:
            return None
        else :
            return item
        
    
    def _setitem(self, k, v):
        hv = self._hash_value(k)
        if self._hash_tbl[hv] is None:# 해당 hash값에 대한 Bucket이 존재하지 않으면 Bucket을 만들고 setValue
            self._hash_tbl[hv] = Bucket()
        bucket = self._hash_tbl[hv]
        bucket._setitem(k, v)

    def _delitem(self, k):
        hv = self._hash_value(k)
        bucket = self._hash_tbl[hv]
        bucket._delitem(k)
        self._num_entry-=1#요소 삭제하고 entry개수 하나 삭제

    def __str__(self):
        s = ''
        for h in range(len(self._hash_tbl)):
            bucket = self._hash_tbl[h]
            if bucket is not None:
                s += "bucket[{:2d}] : ".format(h)
                for item in bucket:
                    s += str(item) + ", "
            s += "\n "
        return s
HashMap_Capacity = 20
print("Creating a HashMap of capacity ({})".format(HashMap_Capacity))
hsMap=HashMap_Bucket(table_size=HashMap_Capacity)
L_students=[
    ("Kim Y-S", 21801234, "ICE", 4.57),
    ("Park S-J", 21916754, "CS", 3.55),
    ("Hong C-H", 22017123, "EE", 4.58),
    ("Lee W-S", 22016321, "ME", 4.54),
    ("Yoon C-M", 22015987, "ICE", 3.87),
    ("Moon J-K", 22018987, "CHEM", 4.55),
    ("Kwon S-S", 22017521, "CS", 4.54),
    ("Kim C-M", 21917987, "ICE", 3.97),
    ("Song M-K", 21818987, "CHEM", 4.59),
    
    ("Kim J-H", 21801234, "ICE", 4.57),
    ("Park J-S", 21916754, "CS", 3.55),
    ("Hwang J-H", 22017123, "EE", 4.58),
    ("Jung J-H", 22016321, "ME", 4.54),
    ("Pang E-J", 22015987, "ICE", 3.87),
    ("Lee E-J", 22018987, "CHEM", 4.55),
    ("Nam S-Y", 22017521, "CS", 4.54),
    ("Moon S-J", 21917987, "ICE", 3.97),
    ("Sung S-G", 21818987, "CHEM", 4.59),
    
    ("Ji C-M", 21917987, "ICE", 3.97),
    ("Song D-G", 21818987, "CHEM", 4.59)
]
for i in range(len(L_students)):
    entry =L_students[i]
    key = entry[0]
    hsMap._setitem(key, entry)
print("Current HashMap Internal Structure:\n", hsMap)
print("Testing searches of HashMap")
while True:
    name = input("student's name to search : ")
    if name == '.':
        break
    student_record = hsMap._getitem(name)
    if student_record == None:
        print("student record with key ({}) was not found !!".format(name))
    else:
        print("student record with key ({}) : ({})".format(key, student_record))