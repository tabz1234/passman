#include "parse_arguments.hpp"

#include <string_view>

#include "../err_msg.hpp"
#include "function/identifiers.hpp"

using namespace Passman::CmdLine;

std::pair<std::vector<Function::OverloadingSet>, std::vector<int>>
Passman::CmdLine::parse_arguments(const int argc, const char** const argv, Passman::Settings& app_settings) noexcept
{
    std::vector<Function::OverloadingSet> fun_vec;
    fun_vec.reserve(argc);

    std::vector<int> index_vec;
    index_vec.reserve(argc);

    auto to_sv = [](const char* const c_str) {
        return std::string_view{c_str};
    };

    auto on_quiet_override = [&l_app_settings = app_settings] {
        l_app_settings.quiet_ = true;
    };
    auto on_interactive_override = [&l_app_settings = app_settings] {
        l_app_settings.interactive_ = true;
    };

    for (int i = 1; i < argc; ++i) {
        if (argv[i][0] == '-') {
            if (argv[i][1] == '\0') [[unlikely]] { // trailing dash
                continue;
            }
            else if (argv[i][1] == '-') { // long option
                auto&& long_option = to_sv(argv[i]);

                long_option.remove_prefix(2); // remove --

                if (long_option == "quiet") {
                    on_quiet_override();
                }
                else if (long_option == "interactive") {
                    on_interactive_override();
                }
                else [[unlikely]] { // user mistake
                    err_msg("Unknown long command line option :\"--", long_option, "\"");
                }
            }
            else { // short option
                int ch_iter = 1;
                bool reached_null = false;
                while (!reached_null) {
                    switch (argv[i][ch_iter]) {
                    case '\0': reached_null = true; break;
                    case 'q': on_quiet_override(); break;
                    case 'i': on_interactive_override(); break;
                    default: [[unlikely]] err_msg("Unknown short command line option :\"-", argv[i][ch_iter], "\""); break; // user mistake
                    }
                    ++ch_iter;
                }
            }
        }
        else if (to_sv(argv[i]) == "get") {
            bool zero_arg_overload =
                argv[i + 1] == nullptr ||
                !(std::find(Function::identifiers.begin(), Function::identifiers.end(), argv[i + 1]) == Function::identifiers.end());

            index_vec.emplace_back(i);
            if (zero_arg_overload) {
                fun_vec.emplace_back(Function::get_0arg);
            }
            else {
                fun_vec.emplace_back(Function::get_1arg);
                ++i;
            }
        }
        else if (to_sv(argv[i]) == "add") {
        }
        else [[unlikely]] { // user mistake
            err_msg("Unknown function :\"", to_sv(argv[i]), "\"");
        }
    }

    return {fun_vec, index_vec};
}
