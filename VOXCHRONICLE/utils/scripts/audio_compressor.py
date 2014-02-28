# -*- coding: utf-8 -*-
#
# graphic_compressor.py
# created by giginet on 2013/04/14
#
import os
import sys
import commands

COMMAND = r'afconvert -f caff -d ima4@%s -c 2 %s.wav %s.caf' # speed color
if __name__ == '__main__':
    src = os.getcwd()
    if len(sys.argv) > 2:
        src = sys.argv[1]
        bitrate = sys.argv[2]
    files = os.listdir(src)
    for file in files:
        filename, ext = os.path.splitext(file)
        if ext == '.wav':
            f = os.path.join(src, filename)
            print file
            print commands.getoutput(COMMAND % (bitrate, f, f))
            


