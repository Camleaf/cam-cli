#sudo pacman -Syu
#paru -Syu


echo "Setting up VCPKG"


if [[ ! "$(basename "$PWD")" == "cam-cli" ]]; then
    echo "Make sure PWD is in cam-cli"
    exit
fi
# add setup conditional on if vcpkg is already insatlled

if [ ! -d "$PWD/vcpkg" ]; then
    git clone git@github.com:microsoft/vcpkg.git
    cd vcpkg || exit 1
    ./bootstrap-vcpkg.sh
else
    echo "VCPKG already exists"
fi
