#!python3
# -*- coding: utf-8 -*-

# This file is part of the libopencm3 project.
# 
# Copyright (C) 2016 Oliver Meier <h2obrain@gmail.com>
#
# This library is free software: you can redistribute it and/or modify
# it under the terms of the GNU Lesser General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# This library is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU Lesser General Public License for more details.
#
# You should have received a copy of the GNU Lesser General Public License
# along with this library.  If not, see <http://www.gnu.org/licenses/>.
#


from sys import argv
from os.path import isfile, dirname, basename, splitext, join
from PIL import Image, ImageFont, ImageDraw
import codecs

print(len(argv),argv)

if len(argv)<3 or len(argv)>4 or (len(argv)==4 and not isfile(argv[3])) :
	print("usage: ./Create_Font.py ./font.ttf fontsize [charsetfile-utf8.txt]")
	print(" - ./font.ttf can also be ./font.pcf or something like Arial or so")
	exit(0)

fontfile = argv[1]
fontsize = None
try :
	fontsize = int(argv[2])
except :
	print("Fontsize is not a number!")
	exit(0)

if len(argv)==4 :
	charsetfile = argv[3]
else :
	charsetfile = join(dirname(argv[0]),"default_charset.txt")
	

#fontfile    = "Tamsyn5x9r.pcf"
#fontfile    = "Tamsyn5x9b.pcf"
#fontfile    = "/usr/share/fonts/liberation/LiberationMono-Regular.ttf"
#fontfile    = "/usr/share/fonts/liberation/LiberationMono-Bold.ttf"
#fontfile    = "/usr/share/fonts/dejavu/DejaVuSansMono.ttf"
#fontfile    = "/usr/share/fonts/dejavu/DejaVuSansMono-Bold.ttf"
#fontfile    = "/usr/share/fonts/gnu-free/FreeMono.ttf"
#fontfile    = "Arial"
#fontsize    = 9
datasize    = 32

charset     = codecs.open(charsetfile,'r','utf-8').read().replace('\n','').replace('\r','')
# sort charset and remove duplicates
charset     = ''.join(sorted(set(charset), key=charset.index))
font        = ImageFont.truetype(fontfile,size=fontsize)

filtered_charset = ""
for c in charset :
	if c!=' ' :
		m,o  = font.getmask2(c, mode="1")
		if m.getbbox()==None :
			print("Dropping:",c.encode('utf-8'))
			continue
	filtered_charset+=c
charset = filtered_charset
			


#render all the text (needed to determine img size)
dummy_img,offset = font.getmask2(charset, mode="1")

ascent,descent  = font.getmetrics()
lineheight      = dummy_img.size[1]+offset[1]
charwidth       = font.getsize("MMM")[0]-font.getsize("MM")[0]
totalwidth      = charwidth*len(charset)
charset_imgsize = (totalwidth,lineheight)


mono_charset_image = Image.new(mode="1", size=charset_imgsize)
ImageDraw.Draw(mono_charset_image, mode="1").rectangle(((0,0),charset_imgsize), fill=0, outline=None)
a4_charset_image   = Image.new(mode="L", size=charset_imgsize)
ImageDraw.Draw(a4_charset_image, mode="L").rectangle(((0,0),charset_imgsize), fill=0, outline=None)
offx=0


fontname       = splitext(basename(fontfile))[0]+"_"+str(fontsize)
fontname       = fontname.replace("-","_")

print("Creating font", fontname)

fmt = "0x{{:0{}x}},".format(datasize//8*2)

mono_chars_table_name  = "mono_chars_"+fontname
mono_chars_table       = "static const char_t "+mono_chars_table_name+"[] = {\n\t"
mono_data_table_name   = "mono_chars_data_"+fontname
mono_data_table        = "static const uint"+str(datasize)+"_t "+mono_data_table_name+"[] = {"
mono_data_table_offset = 0; mv=0; mi=0;

a4_chars_table_name    = "a4_chars_"+fontname
a4_chars_table         = "a4_static const char_t "+a4_chars_table_name+"[] = {\n\t"
a4_data_table_name     = "chars_data_"+fontname
a4_data_table          = "static const uint"+str(datasize)+"_t "+a4_data_table_name+"[] = {"
a4_data_table_offset   = 0; a4v=0; a4i=0;

def add_char(c, mode, chars_table, data_table, data_table_name, data_table_offset, offx, charset_image, set_pixel, finish_data_table_entry):
	x1 = y1 = x2 = y2 = 0
	bbox = (0,0,0,0)
	if c!=' ' :
		m,o  = font.getmask2(c, mode=mode)
		bbox = m.getbbox()
		x1   = (charwidth - bbox[2])/2
		y1   = (o[1]-offset[1] + bbox[1])
		x2   = x1 + bbox[2]-bbox[0]
		y2   = y1 + bbox[3]-bbox[1]
		
	
	# fill data in chars table
	chars_table+= """{{
		.utf8_value = {:d},
		.bbox       = {{ {: 2.0f},{: 2.0f},{: 2.0f},{: 2.0f} }},
		.data       = &{:s}[{:d}]
	}}, """.format(
		ord(c),
		x1,y1,x2,y2,
		data_table_name,data_table_offset
	)
	
	# fill data in chars data table
	data_table+= "\n\t/* '{:s}' */\n\t".format(c)
	
	mi=0; mv=0; lc=0
	for y in range(bbox[1],bbox[3]) :
		for x in range(bbox[0],bbox[2]) :
			px = m.getpixel((x,y))
			# dummy image
			if px : charset_image.putpixel((int(offx+x),int(y)),px)
			
			data_table,data_table_offset, mi,mv,lc = set_pixel(data_table,data_table_offset, px, mi,mv,lc)
	
	# finish last data_table entry
	data_table, data_table_offset = finish_data_table_entry(data_table,data_table_offset, mv,lc)
	
	return chars_table, data_table

def mono_set_pixel(data_table,data_table_offset, px, mi,mv,lc):
	mv |= (px==255) << mi
	mi+=1
	if mi==datasize :
		if lc > 0 : data_table += " "
		data_table += fmt.format(mv)
		mi=0; mv=0
		data_table_offset += 1
		lc+=1
		if lc==4 :
			data_table += "\n\t"
			lc=0
	return data_table,data_table_offset, mi,mv,lc
def mono_finish_data_table_entry(data_table,data_table_offset, mv,lc):
	if mv!=0 :
		if lc > 0 : data_table += " "
		data_table += fmt.format(mv)
		data_table_offset += 1
	elif lc==0 :
		data_table = data_table[:-1]
	return data_table, data_table_offset

for c in charset :
	print(c, end="")
	mono_chars_table, mono_data_table = add_char(
		 		c, "1",
				mono_chars_table,
				mono_data_table, mono_data_table_name, mono_data_table_offset,
				offx, mono_charset_image,
				mono_set_pixel, mono_finish_data_table_entry)
	"""
   	a4_chars_table, a4_data_table = add_char(
   				c, "L",
				a4_chars_table,
				a4_data_table, a4_data_table_name, a4_data_table_offset,
				a4_charset_image)
	"""
	offx += charwidth
	
mono_data_table  = mono_data_table[:-1] + "\n};"

mono_chars_table = mono_chars_table[:-2] + "\n};"


mono_charset_image.save(fontname+".pbm")


fnu = fontname.upper()

fontsize_definition   = "{:s} {:d}".format(fnu,fontsize)

header_filename       = "{:s}.h".format(fontname)
header_file = """
#ifndef _{:s}_
#define _{:s}_

#include <stdint.h>
#include "fonts.h"

extern const font_t font_{:s};

#endif
""".format(
	fnu,fnu,
	fontname
)

c_filename       = "{:s}.c".format(fontname)
c_file = """
#include "{:s}"

{:s}

{:s}

const font_t font_{:s} = {{
	.fontsize       = {:d},
	.lineheight     = {:d},
	.ascent         = {:d},
	.descent        = {:d},
	.charwidth      = {:d},
	.char_count     = {:d},
	.chars          = {:s},
	.chars_data     = {:s},
}};

""".format(
	header_filename,
	mono_data_table,
	mono_chars_table,
	fontname, fontsize, lineheight, ascent, descent, charwidth,
	len(charset),mono_chars_table_name, mono_data_table_name,
)


open(header_filename,'w').write(header_file)
open(c_filename,'w').write(c_file)

print("\ndone.")
