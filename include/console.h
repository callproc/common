#pragma once

#define WIN32_LAZY_AND_MEAN

#include <Windows.h>

#include <string_view>
#include <format>
#include <print>
#include <source_location>
#include <filesystem>
#include <utility>

namespace console {
    namespace detail {
        namespace color {
            inline constexpr std::string_view reset = "\033[0m";
            inline constexpr std::string_view bold = "\033[1m";
            inline constexpr std::string_view dim = "\033[2m";

            inline constexpr std::string_view black = "\033[30m";
            inline constexpr std::string_view red = "\033[31m";
            inline constexpr std::string_view green = "\033[32m";
            inline constexpr std::string_view yellow = "\033[33m";
            inline constexpr std::string_view blue = "\033[34m";
            inline constexpr std::string_view magenta = "\033[35m";
            inline constexpr std::string_view cyan = "\033[36m";
            inline constexpr std::string_view white = "\033[37m";
        } // namespace color

        enum class level { trace, debug, info, warn, error, fatal };

        inline level g_min_level = level::trace;

        [[nodiscard]]
        constexpr std::string_view level_label(level lvl) noexcept {
            switch (lvl) {
            case level::trace: return "TRACE";
            case level::debug: return "DEBUG";
            case level::info:  return "INFO";
            case level::warn:  return "WARN";
            case level::error: return "ERROR";
            case level::fatal: return "FATAL";
            }
            std::unreachable();
        }

        [[nodiscard]]
        constexpr std::string_view level_color(level lvl) noexcept {
            switch (lvl) {
            case level::trace: return color::dim;
            case level::debug: return color::cyan;
            case level::info:  return color::green;
            case level::warn:  return color::yellow;
            case level::error: return color::red;
            case level::fatal: return color::red;
            }
            std::unreachable();
        }

        inline void emit(level lvl, std::string_view msg, const std::source_location loc = std::source_location::current()) {
            if (lvl < g_min_level) return;

            const auto color = level_color(lvl);
            const auto label = level_label(lvl);
            const auto path = std::filesystem::path(loc.file_name());

            std::println("{}[{}]{} {} {}({}:{}){} ", color, label, color::reset, msg, color::dim, path.filename(), loc.line(), color::reset);
        }
    } // namespace detail

    inline void open(const std::string_view title = "console") noexcept {
        AllocConsole();
        SetConsoleTitleA(title.data());

        FILE* fp;
        freopen_s(&fp, "CONOUT$", "w", stdout);
        freopen_s(&fp, "CONOUT$", "w", stderr);
        freopen_s(&fp, "CONIN$", "r", stdin);

        const HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);
        DWORD mode = 0;
        GetConsoleMode(out, &mode);
        SetConsoleMode(out, mode | ENABLE_VIRTUAL_TERMINAL_PROCESSING);

        SetConsoleOutputCP(CP_UTF8);
    }

    inline void close() noexcept {
        FreeConsole();
    }

    inline void set_level(detail::level lvl) noexcept {
        detail::g_min_level = lvl;
    }

    template<typename... Args>
    inline void trace(std::format_string<Args...> fmt, Args&&... args, const std::source_location loc = std::source_location::current()) {
        detail::emit(detail::level::trace, std::format(fmt, std::forward<Args>(args)...), loc);
    }

    template<typename... Args>
    inline void debug(std::format_string<Args...> fmt, Args&&... args, const std::source_location loc = std::source_location::current()) {
        detail::emit(detail::level::debug, std::format(fmt, std::forward<Args>(args)...), loc);
    }

    template<typename... Args>
    inline void info(std::format_string<Args...> fmt, Args&&... args, const std::source_location loc = std::source_location::current()) {
        detail::emit(detail::level::info, std::format(fmt, std::forward<Args>(args)...), loc);
    }

    template<typename... Args>
    inline void warn(std::format_string<Args...> fmt, Args&&... args, const std::source_location loc = std::source_location::current()) {
        detail::emit(detail::level::warn, std::format(fmt, std::forward<Args>(args)...), loc);
    }

    template<typename... Args>
    inline void error(std::format_string<Args...> fmt, Args&&... args, const std::source_location loc = std::source_location::current()) {
        detail::emit(detail::level::error, std::format(fmt, std::forward<Args>(args)...), loc);
    }

    template<typename... Args>
    inline void fatal(std::format_string<Args...> fmt, Args&&... args, const std::source_location loc = std::source_location::current()) {
        detail::emit(detail::level::fatal, std::format(fmt, std::forward<Args>(args)...), loc);
    }
} // namespace console