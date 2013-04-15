import os
from PIL import Image

SRC = "Retina"
DST = "Image"
IGNORES = ['cyber_default', 'cave_default', 'grass_default']

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
    files = os.listdir(SRC)
    base = os.getcwd()
    for file in files:
        filename, ext = os.path.splitext(file)
        print filename
        if ext == '.png' and not filename in IGNORES:
            original = Image.open(os.path.join(base, SRC, file))
            width, height = original.size
            tmb = original.resize((width / 2, height / 2), Image.ANTIALIAS)
            tmb.save(os.path.join(base, DST, '%s%s' % (filename, ext)))
