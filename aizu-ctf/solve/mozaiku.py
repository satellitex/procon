import Image
img = Image.open("./mozaiku.png");

res = "";
for i in range(290,-1,-10):
    print img.getpixel((0,i));
    res += chr( img.getpixel((0,i))[1] );

for i in range(0,300,10):
    res += chr( img.getpixel((i,0))[2] );



print res;
