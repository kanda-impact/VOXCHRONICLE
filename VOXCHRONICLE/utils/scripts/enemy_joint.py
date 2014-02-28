# -*- coding: utf-8 -*-
#
# enemy_joint.py
# created by giginet on 2013/03/23
#
import os
import sys
import itertools
import re
import math
import commands
from PIL import Image
ENEMY_PATTERN = r'(w_)?(?P<name>.+)\d.png'

current = os.getcwd()

def next_power_of_two(num):
    return int(math.pow(2, math.ceil(math.log(num, 2))))

def count_frame(enemy_name):
    for i in itertools.count():
        if not os.path.exists(os.path.join(current, '%s%d.png' % (enemy_name, i))):
            return i

def join_image(enemy_name, is_texture):
    original = Image.open("%s0.png" % enemy_name)
    width, height = original.size
    has_frame = os.path.exists(os.path.join(current, 'w_%s0.png' % enemy_name))
    has_attack = os.path.exists(os.path.join(current, '%s_attack0.png' % enemy_name))
    has_death = os.path.exists(os.path.join(current, '%s_death0.png' % enemy_name))
    frame = count_frame(enemy_name)
    new_size = (width * frame, height * (4 if has_attack or has_death else 2))
    texture_size = next_power_of_two(max(new_size))
    size = (texture_size, texture_size) if is_texture else new_size
    dst = Image.new('RGBA', size)
    for f in xrange(frame):
        enemy_image = Image.open(os.path.join(current, '%s%d.png' % (enemy_name, f))) 
        dst.paste(enemy_image, (width * f, 0))
        if has_frame:
            frame_image = Image.open(os.path.join(current, 'w_%s%d.png' % (enemy_name, f)))
            dst.paste(frame_image, (width * f, height))
    if has_attack:
        attack_image = Image.open(os.path.join(current, '%s_attack0.png' % enemy_name))
        attack_frame_image = Image.open(os.path.join(current, 'w_%s_attack0.png' % enemy_name))
        dst.paste(attack_image, (0, height * 2))
        dst.paste(attack_frame_image, (0, height * 3))
    if has_death:
        death_image = Image.open(os.path.join(current, '%s_death0.png' % enemy_name))
        death_frame_image = Image.open(os.path.join(current, 'w_%s_death0.png' % enemy_name))
        dst.paste(death_image, (width, height * 2))
        dst.paste(death_frame_image, (width, height * 3))
    return dst


if __name__ == '__main__': 
    cache = []
    files = os.listdir(current)
    for filename in files:
        is_texture = len(sys.argv) >= 2 and sys.argv[1] == '--texture'
        match = re.match(ENEMY_PATTERN, filename)
        if match:
            name = match.group('name')
            if name in cache: continue
            if name.endswith('attack') or name.endswith('death'): continue
            print name
            cache.append(name)
            dst = join_image(name, is_texture)
            dst.save(os.path.join(current, '%s.png' % name))
            if is_texture:
                print commands.getoutput('texturetool -e PVRTC -o %s.pvr %s.png' % (os.path.join(current, name), os.path.join(current, name))) 
