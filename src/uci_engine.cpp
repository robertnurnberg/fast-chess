#include "uci_engine.h"
#include "engine_config.h"

#include <sstream>
#include <stdexcept>

void UciEngine::setConfig(const EngineConfiguration &rhs)
{
    config = rhs;
}

void UciEngine::sendUciNewGame()
{
    writeProcess("ucinewgame");
    isResponsive();
}

void UciEngine::sendUci()
{
    writeProcess("uci");
}

std::vector<std::string> UciEngine::readUci()
{
    bool timeout = false;
    return readProcess("uciok", timeout);
}

std::string UciEngine::buildGoInput(Color stm, TimeControl tc)
{
    std::stringstream input;
    input << "go";

    if (config.nodes != 0)
        input << " nodes " << config.nodes;

    if (config.plies != 0)
        input << " depth " << config.plies;

    if (tc.time != 0)
        input << (stm == WHITE ? " wtime " : " btime ") << tc.time;

    if (tc.increment != 0)
        input << (stm == WHITE ? " winc " : " binc ") << tc.increment;

    if (tc.moves != 0)
        input << " movestogo " << tc.moves;

    return input.str();
}

void UciEngine::loadConfig(const EngineConfiguration &config)
{
    this->config = config;
}

void UciEngine::sendQuit()
{
    writeProcess("quit");
}

void UciEngine::sendSetoption(const std::string &name, const std::string &value)
{
    writeProcess("setoption name " + name + " value " + value);
}

void UciEngine::sendGo(const std::string &limit)
{
    writeProcess("go " + limit);
}

void UciEngine::startEngine()
{
    initProcess(config.cmd);

    sendUci();
    readUci();

    if (!pingEngine())
    {
        throw std::runtime_error("Something went wrong when pinging the engine.");
    }

    for (const auto &option : config.options)
    {
        sendSetoption(option.first, option.second);
    }
}

void UciEngine::startEngine(const std::string &cmd)
{
    initProcess(cmd);

    sendUci();
    readUci();

    if (!pingEngine())
    {
        throw std::runtime_error("Something went wrong when pinging the engine.");
    }

    for (const auto &option : config.options)
    {
        sendSetoption(option.first, option.second);
    }
}

void UciEngine::stopEngine()
{
    sendQuit();
    killProcess();
}