#ifndef PW_MANAGER
#define PW_MANAGER

#include <nlohmann/json.hpp>
using json = nlohmann::json;

json readFileAsJSON(std::string masterPassword);

#endif
