#ifndef REPORTING_H
#define REPORTING_H

#include <string>
#include <vector>

class Reporting {
public:
    void reportError(const std::string& message, int line);
    void printErrors() const;

private:
    std::vector<std::string> errors; // Store error messages
};

#endif // REPORTING_H
