# check all C++ versions at once
for v in c++98 c++11 c++14 c++17 c++20 c++23; do
    echo -n "$v: "
    gcc -std=$v -xc++ -E -dM /dev/null 2>/dev/null | grep __cplusplus || echo "Not Supported"
done
