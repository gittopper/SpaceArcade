#/bin/sh
#
# converts mp3 to ogg
#Dependent on: mp3info , mpg123 , vorbis-tools (go to Synaptic, search, and install)


function mp3-ogg () {

if [ ! -f "$1" ]; then

  echo "File "$1" not found!"

else

  mp3info -p "title%t\nartist%a\nalbum%l\nbitrate%r\n" "$1" > tag.txt
  
  title=$(cat tag.txt | grep title | cut -c 6-50)
  artist=$(cat tag.txt | grep artist | cut -c 7-50)
  album=$(cat tag.txt | grep album | cut -c 6-50)
  bitrate=$(cat tag.txt | grep bitrate | cut -c 8-50)

  if [ "$bitrate" -ge 256 ];then
    quality=8
  elif [ "$bitrate" -ge 192 ];then
    quality=7
  elif [ "$bitrate" -ge 128 ];then
    quality=6
  else
    quality=5
  fi

  wav=`echo "$1"|sed -e 's/.[mM][pP]3/.wav/'`
  notag=`echo "$1"|sed -e 's/.[mM][pP]3/.ogg/'`
  mpg123 --wav "$wav" "$1" &&
  oggenc -q $quality -t "$title" -a "$artist" -l "$album" -o "$notag" "$wav"
  rm tag.txt
  rm -f "$wav" ||
  echo "There was a problem with the conversion process!"

fi

}



# convert all mp3 files in directory

if [ $# -eq 1 -a -d "$1" ]; then

for file in $1/*.[mM][pP]3; do
    mp3-ogg "$file"
done
exit

fi

# One or more mp3 files were given

for file in $*; do

  mp3-ogg "$file"

done

# Not enough information

if [ $# -lt 1 ]; then

  echo
  echo "Usage:	$0 myfile.mp3"
  echo "	$0 /directory/containing/mp3/files"
  echo "	$0 myfile.mp3 myfile2.mp3 myfile3.mp3"
  # You have to use quotations for the arguement below.
  # Failure to do so will result in only one file being
  # converted. Namely, the first one it comes across...
  echo '	$0 "*.mp3"'
  echo
  echo "For converting .mp3's that have spaces in the"
  echo 'name, use the directory option OR "*.mp3"'
  echo
  exit

fi

exit