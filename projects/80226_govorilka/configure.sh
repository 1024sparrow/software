#!/bin/bash
#

mkdir bin

cd bin
echo "#!/bin/bash" > start.sh
echo "#" >> start.sh
echo "" >> start.sh
echo "export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:`pwd`" >> start.sh
#echo "LD_LIBRARY_PATH=$LD_LIBRARY_PATH:." >> start.sh
echo "`pwd`/80226_govorilka \$*" >> start.sh
#echo "./enbook \$*" >> start.sh

chmod +x start.sh
cd ..
