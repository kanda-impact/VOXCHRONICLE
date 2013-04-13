# -*- coding: utf-8 -*-
#
# graphic_compressor.py
# created by giginet on 2013/04/14
#
SRC = "Retina"
import os
import commands

COMMAND = r'pngquant --speed %d --force --ext .png %d %s.png' # speed color
if __name__ == '__main__':
    files = os.listdir(SRC)
    for file in files:
        filename, ext = os.path.splitext(file)
        if ext == '.png':
            print commands.getoutput(COMMAND % (1, 256, os.path.join(SRC, filename)))
