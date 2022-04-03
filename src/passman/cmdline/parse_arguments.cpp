#include "parse_arguments.hpp"

#include <string_view>

#include "../../util/ExitCode.hpp"
#include "../../util/fcheck.hpp"

#include "../err_msg.hpp"
#include "function/identifiers.hpp"
#include <unistd.h>

using namespace Passman::CmdLine;

std::pair<std::vector<Function::OverloadingSet>, std::vector<int>>
Passman::CmdLine::parse_arguments(const int argc, const char** const argv, Passman::Settings& app_settings) noexcept
{
    std::vector<Function::OverloadingSet> fun_vec;
    fun_vec.reserve(argc);

    std::vector<int> index_vec;
    index_vec.reserve(argc);

    auto on_quiet_override = [&l_app_settings = app_settings]() noexcept {
        l_app_settings.quiet_ = true;
    };
    auto on_interactive_override = [&l_app_settings = app_settings]() noexcept {
        l_app_settings.interactive_ = true;
    };
    const auto on_help = []() noexcept {
        const char help_txt[] =
#include "../../../blob/help.txt"
            "\n";

        tprinter.flush();
        write(STDOUT_FILENO, help_txt, sizeof(help_txt));

        std::exit(exit_failure);
    };

    const auto is_fun_id = [](const std::string_view sv) noexcept {
        return !(std::find(Function::identifiers.begin(), Function::identifiers.end(), sv) == Function::identifiers.end());
    };

    bool user_made_mistake = false;

    for (int i = 1; i < argc; ++i) {
        std::string_view cur_opt = argv[i];

        if (cur_opt[0] == '-') {
            if (cur_opt[1] == '\0') [[unlikely]] { // trailing dash
                continue;
            }
            else if (cur_opt[1] == '-') { // long option
                cur_opt.remove_prefix(2); // remove --

                if (cur_opt == "quiet") {
                    on_quiet_override();
                }
                else if (cur_opt == "interactive") {
                    on_interactive_override();
                }
                else if (cur_opt == "help") {
                    on_help();
                }
                else [[unlikely]] { // user mistake
                    err_msg("Unknown long command line option :\"--", cur_opt, "\"");
                    user_made_mistake = true;
                }
            }
            else { // short option
                int ch_iter = 1;
                bool reached_null = false;

                while (!reached_null) {
                    switch (cur_opt[ch_iter]) {
                    case '\0': reached_null = true; break;
                    case 'q': on_quiet_override(); break;
                    case 'i': on_interactive_override(); break;
                    case 'h': on_help(); break;
                    default:
                        [[unlikely]]
                        {
                            err_msg("Unknown short command line option :\"-", cur_opt[ch_iter], "\"");
                            user_made_mistake = true;
                            break; // user mistake
                        }
                    }
                    ++ch_iter;
                }
            }
        }
        else if (cur_opt == "get") {
            const bool zero_arg_overload = argv[i + 1] == nullptr || is_fun_id(argv[i + 1]);

            index_vec.emplace_back(i);

            if (zero_arg_overload) {
                fun_vec.emplace_back(Function::get_0arg);
            }
            else {
                fun_vec.emplace_back(Function::get_1arg);
                ++i;
            }
        }
        else if (cur_opt == "add") {

            if (i == (argc - 1) || is_fun_id(argv[i + 1])) [[unlikely]] { // user mistake
                err_msg("You must call function add with one(login) or two(login and password) arguments");
                user_made_mistake = true;
                continue;
            }

            index_vec.emplace_back(i);

            const bool one_arg_overload = argv[i + 2] == nullptr || is_fun_id(argv[i + 2]);
            if (one_arg_overload) {
                fun_vec.emplace_back(Function::add_1arg);
                ++i;
            }
            else {
                fun_vec.emplace_back(Function::add_2arg);
                i += 2;
            }
        }
        else [[unlikely]] { // user mistake
            err_msg("Unknown function :\"", cur_opt, "\"");
            user_made_mistake = true;
        }
    }

    fcheck(!user_made_mistake, [] {
        err_msg("You made mistake in command line options, try 'passman --help' for more information.");
        println("Exiting ...");
        std::exit(exit_failure);
    });

    return {fun_vec, index_vec};
}
