dirname=$1
dirname=/mnt/d/compro-solver/codeforces/${dirname}
mkdir -p $dirname
cd $dirname
for i in {A..F}
do
filename=${i}.cpp
if [ ! -e filename ]; then
    cat ../../solver/F.cpp > $filename
fi
done
