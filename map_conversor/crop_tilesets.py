#!./env/bin/python
# -*- coding: ascii -*-
import sys
import cv2
import xml.dom.minidom

in_xml = sys.argv[1]

doc = xml.dom.minidom.parse(in_xml)

if doc==None:
    sys.exit(in_xml + "not found")

tileset_xml = doc.getElementsByTagName('tileset')[0]
image_xml = doc.getElementsByTagName('image')[0]

w = int(tileset_xml.getAttribute("tilewidth"))
h = int(tileset_xml.getAttribute("tileheight"))
img_file = image_xml.getAttribute("source")

file_name = img_file.split(".")[0]

path = in_xml.split("/")

folders_path = path[:-1]
f = path[-1]
xml_file_name = f.split(".")[0]

folder_path = ""
tile_name = xml_file_name + "_t"

for folder in folders_path:
    folder_path = folder_path + folder
    folder_path = folder_path + "/"

in_img = folder_path + img_file

tiles = 1
x = 0
y = 0

img = cv2.imread(in_img, cv2.IMREAD_UNCHANGED)

img_height = img.shape[0]
img_width = img.shape[1]


tex_file_name = "gfx/" + xml_file_name + ".t3s"
tex_file_header = "--atlas -f rgba8888 -z auto\n"

f = open(tex_file_name, "w")
f.write(tex_file_header)

while True:
    
    tile_path = folder_path + xml_file_name + "/" + tile_name + str(tiles) + ".png"

    crop_img = img[y:y+h, x:x+w]

    xc = 0
    yc = 0

    color = False

    while (yc<h and color==False):
        xc = 0
        while (xc<w and color==False):
            for c in crop_img[yc, xc]:
                if c!=0:
                    color = True
                    break
            xc += 1
        yc += 1
            
    if color==True:
        print(tile_path)
        cv2.imwrite(tile_path, crop_img)
        f.write(tile_path + "\n")
        tiles = tiles + 1

    x = x + w
    if x >= img_width:
        x = 0
        y = y + h
        if y >= img_height:
            break

