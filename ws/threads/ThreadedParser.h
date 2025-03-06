#ifndef THREADED_PARSER_H
#define THREADED_PARSER_H

#include <vector>
#include <mutex>
#include <condition_variable>
#include <thread>

class ThreadedParser {
public:
    ThreadedParser();
    ~ThreadedParser();

    void start();
    void receiveData(const std::vector<uint8_t>& data);

private:
    void parsingThreadFunction();
    std::vector<uint8_t> parseData(std::vector<uint8_t>& data);

    std::vector<uint8_t> _activeBuffer;
    std::mutex _bufferMutex;
    std::condition_variable _cv;
    bool _stopParser;
    std::thread _parserThread;
};

#endif // THREADED_PARSER_H
