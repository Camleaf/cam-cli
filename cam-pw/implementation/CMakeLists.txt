add_library(uclient-implementation ioHelper.cpp extLoad.cpp encHelper.cpp)
add_package_to_target("json" "uclient-implementation" FALSE)
add_package_to_target("gpgmepp" "uclient-implementation" FALSE)
