#pragma once

#include <spdlog/sinks/basic_file_sink.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/spdlog.h>

class LogManager
{
public:
    LogManager() = default;
    ~LogManager() = default;
    static LogManager& GetInstance()
    {
        static LogManager instance;
        return instance;
    }
    LogManager(LogManager const&) = delete;
    void operator=(LogManager const&) = delete;
    static void Init()
    {
        auto logger = spdlog::stdout_color_mt("console");
        // auto logger = spdlog::basic_logger_mt("console", "logs/basic-log.txt");
    }
};