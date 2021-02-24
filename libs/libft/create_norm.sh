dir="./for-norme"
m="Makefile"
srcdir="./extra_functions ./main_part ./extra_functions/math_functions"
headers="./include/* ./libft.h"

mkdir -p $dir

#create makefile by finding all .c files and adding '\' at the end of each line.
cat ./sh/mf_p1 > $dir/$m
find $srcdir -name "*.c" -exec basename {} \; | awk 'NF{print $0 "\\"}' >> $dir/$m
cat ./sh/mf_p2 >> $dir/$m

#cp all .c files
find $srcdir -name "*.c" -exec cp {} $dir \;

# move the headers
cp $headers $dir
#cp extra_functions/*.h $dir

unset dir
unset m
unset srcdir
unset headers
