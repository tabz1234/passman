#pragma once

struct false_type {
    bool value = false;
};
struct true_type {
    bool value = true;
};

template <typename T>
struct have_operator_curl_braces : true_type {
    static auto value = T{};
};

template <>
struct have_operator_curl_braces : false_type {
};
