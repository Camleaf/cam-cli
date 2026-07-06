sudo apt update


echo "Installing required system packages"
sudo apt install curl zip unzip tar
sudo apt install libssh-dev openssl linux-libc-dev 



echo "Setting up VCPKG"

# add setup conditional on if vcpkg is already insatlled

if [ ! -d "$HOME/vcpkg" ]; then
    cd "$HOME" || exit 1
    git clone https://github.com/microsoft/vcpkg.git
    cd vcpkg || exit 1
    ./bootstrap-vcpkg.sh
else
    echo "VCPKG already exists"
fi
echo -e 'Add to .bashrc:\nexport VCPKG_ROOT="$HOME/vcpkg"\nexport PATH="$VCPKG_ROOT:$PATH"'
