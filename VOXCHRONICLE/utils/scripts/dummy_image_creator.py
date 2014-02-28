# -*- coding: utf-8 -*-
#
# dummy_image_creator.py
# created by giginet on 2013/02/26
#
import random
import sys
from PIL import Image

if __name__ == '__main__':
    if len(sys.argv) < 4:
        print "usage %s <width> <height> <filename> (<color>)" % sys.argv[0]
    else:
        w, h = map(lambda n : int(n), sys.argv[1:3])
        filename = sys.argv[3]
        color = sys.argv[4] if len(sys.argv) >= 5 else random.randint(0, 2 << 16)
        img = Image.new('RGB', (w, h), color)
        img.save(filename)
