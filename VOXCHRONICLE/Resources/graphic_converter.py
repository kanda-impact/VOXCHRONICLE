import os
import shutil
from PIL import Image

SRC = "Retina"
DST = "Image"

def remove_all(path):
    for (root, dirs, files) in os.walk(path, topdown=False):
      for d in dirs:
        if os.path.islink(os.path.join(root, d)):
          print "rmdir(link): %s (%s + %s) " % (os.path.join(root, d), root, d)
          os.remove(os.path.join(root, d))
        else:
          print "rmdir: %s (%s + %s) " % (os.path.join(root, d), root, d)
          os.rmdir(os.path.join(root, d))
      for f in files:
        print "rm: %s (%s + %s)" % (os.path.join(root, f), root, f)
        os.remove(os.path.join(root, f))
    os.rmdir(path)

if __name__ == '__main__':
    if os.path.exists(DST):
        remove_all(DST)
    shutil.copytree(SRC, DST)
    files = os.listdir(DST)
    base = os.getcwd()
    for file in files:
        filename, ext = os.path.splitext(file)
        if ext == '.png':
            original = Image.open(os.path.join(base, DST, file))
            tmb = original.copy()
            width, height = original.size
            tmb.thumbnail((width / 2, height / 2))
            tmb.save(os.path.join(base, DST, '%s%s' % (filename, ext)))
