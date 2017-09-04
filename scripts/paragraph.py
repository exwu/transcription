#! /usr/bin/python

import sys

lines = [line.rstrip('\n') for line in open(sys.argv[1])]

out_file = open('empath_and_augur.txt', 'w')

broken = False

for line in lines:
    if not broken and len(line) == 0: 
        # paragraph break
        out_file.write('\n\t')
        broken = True
    elif line.strip() == "---": 
        out_file.write('\n\n')
    else: 
        out_file.write(line)
        broken = False



out_file.write('\n')
out_file.close()
