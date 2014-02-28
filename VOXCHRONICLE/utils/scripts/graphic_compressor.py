# -*- coding: utf-8 -*-
#
# graphic_compressor.py
# created by giginet on 2013/04/15
#
import sys
import os
import commands

COMMAND = 'pngquant --speed %(speed)d --quality=%(quality)s --ext %(dst)s %(src)s'
SPEED = 1
QUALITY = '40-60'

if __name__ == '__main__':
    src = sys.argv[1]
    src = os.path.join(os.getcwd(), src)
    for file in os.listdir(src):
        if file.endswith('png'):
            print file
            print commands.getoutput(COMMAND % {'quality' : QUALITY, 'speed' : SPEED, 'src' : os.path.join(src, file), 'dst' : ''})

