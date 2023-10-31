# Requiriments
sudo apt install wget make cmake clang

# Install editline
wget https://github.com/troglobit/editline/releases/download/1.17.1/editline-1.>
tar xf editline-1.1*.tar.gz
rm editline-1.1*.tar.gz
cd editline-1.17.1/
./configure --prefix=/usr
make all
sudo make install
cd ..
rm -rf editline-1.*/
