import os
import sys
import commands
from PIL import Image

SRC = "Original"
DSTS = (
    ("Image", (0.5, 0.5)),
    ("Retina", (1.0, 1.0))
)
IGNORES = ['3d_background0', 'cyber_default', 'cave_default', 'grass_default']
COMPRESS_COMMAND = 'pngquant --speed %(speed)d --quality=%(quality)s --force --ext %(ext)s %(src)s'
SPEED = 1
QUALITY = '50-80'

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
    compress = False
    if len(sys.argv) > 1 and sys.argv[1] == '--compress': compress = True
    files = os.listdir(SRC)
    base = os.getcwd()
    for file in files:
        filename, ext = os.path.splitext(file)
        if ext == '.png' and not filename in IGNORES:
            print filename
            original = Image.open(os.path.join(base, SRC, file))
            width, height = original.size
            for dst, scale in DSTS:
                if int(scale[0]) != 1 or int(scale[1]) != 1:
                    img = original.resize((int(width * scale[0]), int(height * scale[1])), Image.ANTIALIAS)
                else:
                    img = original
                img.save(os.path.join(dst, '%s%s' % (filename, ext)))
                if compress:
                    print commands.getoutput(COMPRESS_COMMAND % {'quality' : QUALITY, 
                        'speed' : SPEED, 
                        'src' : os.path.join(base, dst, file), 
                        'ext' : ext
                    })

