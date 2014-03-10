from disassembler import *

def main():
  d = {}
  d["hello"] = "goodbye"
  d["dog!"] = "cat!"
  d["young"] = "old"
  s = "hello young dog!"
  t = s.split()
  for x in t:
    print(x)
  for x in t:
    print(d[x])
  for x in d.keys():
    print(x, d[x])
  for y in d.values():
    print(y)
  for key in d:
    print(key, d[key])
  print(type(d))
  print(type(type(d)))
#main()

disassemble(main)

#Going to have to create two new classes
#4 files total, .h and .cpp

#Add hash methods to all classes to they are all hashable?
