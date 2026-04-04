if [ -d "./bin" ]; then
    rm -rf ./bin/*  
fi
cd build || exit
rm -rf ./*
cmake ..
make
cd ..
chmod +x ./bin/cam-cli/cam-cli
